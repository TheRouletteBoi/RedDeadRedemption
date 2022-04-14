# Large-Hash-CUDA-Collider
GTA 5 Natives collider CUDA Accelerated



COMPILE PROJECT AND EXECUTE

You should have installed CUDA ( Work only on Windows )

Use NVCC Compiler :
Open a command prompt and go to your directory and execute the command :</br>
nvcc -run -arch=sm_30 -m=64 coll.cu

Use the good arch for your GPU, you can found documentation to compile with NVCC to :</br>
http://docs.nvidia.com/cuda/cuda-compiler-driver-nvcc/#axzz4hoIl0y7H

When the program is launched, the file "NativesGPU.txt" is created in your desktop, the collisions is append to this file.

Bench on GTX 760 : ~14.8 Millions Hashes per second</br>
Bench on GTX 1080 : ~32.4 Millions Hashes per second</br>

You can customise the dictionnaries and update the array of unknowns hashs.

Example output :</br>
0xB802B671 : GET_OBJ_ENTITY</br>
0xD2B8ACBD : IS_COVER_INTERIORS_CYCLE</br>
0x965EA007 : IS_START_POSITION_EXIST_ORIGIN_SC_MESSAGE_ONLY</br>
0x74C16879 : HAS_DISPLAY_STATIC_A_ONGOING_SOCIAL_DEFAULT_JUMP</br>
0xFFB2ADA1 : RESET_TIMER_SESSION_EARN</br>
0x82D32D07 : GET_MEMORY_PLANES_PITCH_JOB_ZOOM_COLLISION_EXPLOSION</br>
0xDB7AECDA : DOES_ACTIVATED_POSITION_SPENT_REMOVE_DRIVER_BANNED_CLOTH</br>
0x39A3CC6F : DOES_ACTIVE_AS_DATA_BEEN_LINE</br>
0xD43BB56D : SET_MUSIC_OUT_SKIP_3D_NEW_LEAVE</br>
0x3FE33BD6 : ARE_FIND_CURSOR_REPLAY</br>


You can also edit the macros in coll.cu to custom the generator natives.

To your GPUs!
