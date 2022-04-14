#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <shlobj.h>
#include <device_launch_parameters.h>
#include <curand.h>
#include <curand_kernel.h>
#include <math.h>
#include <fstream>
#include <ctype.h>
#include "dicts.h"

#define LENGTH 72 // MAX LENGTH OF GENERATE NATIVE
#define MAX_LENGTH_WORD 16 // FOR ALLOC ( CHANGE IF A WORD IN DICT IS TALLER THAN 16 ), WILL BE A MULTIPLE OF 8
#define MIN_WORD_NUM 2 // MINIMUM OF WORDS TO GEN A NATIVE
#define MAX_WORD_NUM 6 // MAXIMUM OF WORDS TO GEN A NATIVE ( IF ERROR CHANGE THE LENGTH MACRO )

#define SIMULTANEOUS 200000 // SIMULTANEOUS NATIVES COUNT GENERATE PER CYCLE KERNEL
#define MAX_GENERATED 1000000 // MAX OUTPUT COLLISIONS

__global__ void initCURAND(curandState* cus, int numElements)
{
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if (i < numElements)
        curand_init(clock64(), i, 0, &(cus[i]));
}

__global__ void colliderKernel(curandState* cus, const char* dictStart, const char* dictArg,
                            const unsigned int* nativesUnk, unsigned short UnkNmb,
                            char* genNat, int numElements, int dictWordLength,
                            int dictStartWordLength)
{
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if (i < numElements)
    {
        char relOut[LENGTH];
        const unsigned char lengthWord64 = MAX_LENGTH_WORD / 8;
        uint64_t wordBuf[lengthWord64];

        const uint64_t* startWord =
            (const uint64_t*)(dictStart + ((unsigned char)(curand(&(cus[i])) % dictStartWordLength) * MAX_LENGTH_WORD));
        for (unsigned char it = 0; it < lengthWord64; it++)
            wordBuf[it] = startWord[it];
        const char* wordBuf8_1 = (const char*)wordBuf;
        
        unsigned char it1 = 0;
        while (wordBuf8_1[it1] != 0x00)
        {
            relOut[it1] = wordBuf8_1[it1];
            it1++;
        }
        relOut[it1] = '_';

        unsigned char randWords = (unsigned char)(curand(&(cus[i])) % (MAX_WORD_NUM - MIN_WORD_NUM)) + MIN_WORD_NUM; // BOUND 2 - 8
        for (unsigned char it2 = 0; it2 < randWords; it2++)
        {
            it1++;
            unsigned short randCurrent = (unsigned short)(curand(&(cus[i])) % dictWordLength);
            const uint64_t* current = (const uint64_t*)(dictArg + (randCurrent * MAX_LENGTH_WORD));
            for (unsigned char it = 0; it < lengthWord64; it++)
                wordBuf[it] = current[it];
            const char* wordBuf8_2 = (const char*)wordBuf;

            unsigned char itRel = 0;
            while (wordBuf8_2[itRel] != 0x00)
            {
                relOut[it1] = wordBuf8_2[itRel];
                it1++;
                itRel++;
            }
            relOut[it1] = '_';
        }
        relOut[it1] = 0x00;

        unsigned char it = 0;
        unsigned int hash = 0;
        while(relOut[it] != 0x00) {
            hash += relOut[it++];
            hash += hash << 10;
            hash ^= hash >> 6;
        }
        hash += hash << 3;
        hash ^= hash >> 11;
        hash += hash << 15;

        bool bypassErase = true;
        for (unsigned short it3 = 0; it3 < UnkNmb; it3++)
        {
            if (hash == nativesUnk[it3]) {
                bypassErase = false;
                break;
            }
        }
        
        if (bypassErase)
            *(genNat + (i * LENGTH)) = 0x00;
        else
        {
            int* relOutGlb = (int*)(genNat + (i * LENGTH));
            int* relOutFour = (int*)relOut;
            for (unsigned char itR = 0; itR < 18; itR++)
                if (relOutFour[itR] != 0x00000000)
                    relOutGlb[itR] = relOutFour[itR];
        }
    }
}

int main(void)
{
    cudaDeviceProp propsDev = {};
    cudaGetDeviceProperties(&propsDev, 0);
    cudaSetDevice(0);
    printf("Selected GPU : %s\n\n", propsDev.name);

    int startWordsSize = sizeof(startWords) / sizeof(startWords[0]);
    char* dictTableStart = NULL;
    int sizeDict = startWordsSize * MAX_LENGTH_WORD;
    cudaMalloc((void**)&dictTableStart, sizeDict);
    char* dictTableStartRAM = new char[sizeDict];
    memset(dictTableStartRAM, 0x00, sizeDict);

    for(int i = 0; i < startWordsSize; i++)
        memcpy(dictTableStartRAM + (i * MAX_LENGTH_WORD), startWords[i], strlen(startWords[i]));

    cudaMemcpy(dictTableStart, dictTableStartRAM, sizeDict, cudaMemcpyHostToDevice);
    delete[] dictTableStartRAM;


    int wordSizeDict = sizeof(words) / sizeof(words[0]);
    sizeDict = wordSizeDict * MAX_LENGTH_WORD;
    char* dictTable = NULL;
    cudaMalloc((void**)&dictTable, sizeDict);
    char* dictTableRAM = new char[sizeDict];
    memset(dictTableRAM, 0x00, sizeDict);

    for(int i = 0; i < wordSizeDict; i++)
        memcpy(dictTableRAM + (i * MAX_LENGTH_WORD), words[i], strlen(words[i]));

    cudaMemcpy(dictTable, dictTableRAM, sizeDict, cudaMemcpyHostToDevice);
    delete[] dictTableRAM;

    printf("Dict start words size : %d entries\nDict words size : %d entries\n", startWordsSize, wordSizeDict);

    // RESULTS
    int sizeGen = SIMULTANEOUS * LENGTH;
    char* genPtr = NULL;
    cudaMalloc((void**)&genPtr, sizeGen);
    char* genRAM = new char[sizeGen];
    memset(genRAM, 0x00, sizeGen);
    cudaMemcpy(genPtr, genRAM, sizeGen, cudaMemcpyHostToDevice);

    unsigned short UnknownsCount = sizeof(unknowns) / sizeof(unknowns[0]);
    unsigned int* UnknownsNat = NULL;
    int sizeNatUnk = UnknownsCount * 4;
    cudaMalloc((void**)&UnknownsNat, sizeNatUnk);
    cudaMemcpy((unsigned char*)UnknownsNat, (unsigned char*)unknowns, sizeNatUnk, cudaMemcpyHostToDevice);

    int thrBloc = 128;
    int blocGrid = (SIMULTANEOUS + thrBloc - 1) / thrBloc;


    // CREATE OUTPUT TEXT
    TCHAR pathSP[1024];
	TCHAR pathSPO[1024];
    memset(pathSP, 0x00, 1024);
	memset(pathSPO, 0x00, 1024);
	SHGetSpecialFolderPath(HWND_DESKTOP, pathSP, CSIDL_DESKTOP, FALSE);
	strcpy_s(pathSPO, pathSP);
    strcat_s(pathSPO, "\\NativesGPU.txt");

    std::ofstream outputText = std::ofstream(pathSPO);
    char* outputBuf = new char[384];
    char* sprOutputBuf = new char[512];
    char* antiDouble = new char[LENGTH * MAX_GENERATED];


    curandState* cuRANDs;
    cudaMalloc((void**)&cuRANDs, sizeof(curandState) * SIMULTANEOUS);
    initCURAND<<<blocGrid, thrBloc>>>(cuRANDs, SIMULTANEOUS);
    printf("Initialised CURAND\n\n");

    // STAT ABOUT
    int perSec = 0;
    int tickSec = GetTickCount();

    for(;;)
    {
        if (GetTickCount() - tickSec >= 1000)
        {
            printf("%d hashs/s\n", perSec);
            perSec = 0;
            tickSec = GetTickCount();
        }

        // EXECUTE HASH KERNEL
        colliderKernel<<<blocGrid, thrBloc>>>(cuRANDs, (const char*)dictTableStart, (const char*)dictTable,
                                                            (const unsigned int*)UnknownsNat, UnknownsCount,
                                                                    genPtr, SIMULTANEOUS, wordSizeDict, startWordsSize);

        cudaMemcpy(genRAM, genPtr, sizeGen, cudaMemcpyDeviceToHost);

        for (int i = 0; i < SIMULTANEOUS; i++)
        {
            char* Output = (genRAM + (i * LENGTH));
            if (*Output != 0x00)
            {
                bool bypassIA = true;
                for (int iA = 0; iA < MAX_GENERATED; iA++)
                {
                    char* CurIA = antiDouble + (iA * LENGTH);
                    if (*CurIA == 0x00)
                    {
                        memcpy(CurIA, Output, strlen(Output));
                        break;
                    }

                    if (!strcmp(Output, CurIA))
                    {
                        bypassIA = false;
                        break;
                    }
                }

                if (bypassIA)
                {
                    unsigned char it = 0;
                    unsigned int hash = 0;
                    while(Output[it] != 0x00) {
                        hash += Output[it++];
                        hash += hash << 10;
                        hash ^= hash >> 6;
                    }
                    hash += hash << 3;
                    hash ^= hash >> 11;
                    hash += hash << 15;

                    sprintf(sprOutputBuf, "0x%2X : %s", hash, Output);
                    unsigned short offset = 0;
                    while (sprOutputBuf[offset] != 0x00) {
                        if (offset != 1)
                            sprOutputBuf[offset] = toupper(sprOutputBuf[offset]);
                        offset++;
                    }

                    outputText << sprOutputBuf << std::endl;
                }
            }
        }

        perSec += SIMULTANEOUS;
    }

    /*
        GARBAGE COLLECTING
    */
    cudaFree(cuRANDs);
    cudaFree((char*)UnknownsNat);
    cudaFree(genPtr);
    cudaFree(dictTable);
    cudaFree(dictTableStart);
    delete[] genRAM;
    outputText.close();

    return 0;
}
