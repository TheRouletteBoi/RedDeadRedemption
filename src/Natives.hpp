#pragma once
#include "Invoker.hpp"

template <typename R, typename... TArgs>
R invoke(rage::scrNativeHash hash, TArgs&... args)
{
   g_Invoker->BeginCall();
   g_Invoker->Push(args...);
   g_Invoker->EndCall(hash);
   return g_Invoker->GetReturn<R>();
}

template <typename R>
R invoke(rage::scrNativeHash hash)
{
   g_Invoker->BeginCall();
   g_Invoker->EndCall(hash);
   return g_Invoker->GetReturn<R>();
}

namespace SYSTEM
{
   static void WAIT(int ms) { invoke<Void>(0x7715C03B, ms); } // 0x7715C03B
   static void WAITUNWARPED(int ms) { invoke<Void>(0x01185F9B, ms); } // 0x01185F9B
   static void WAITUNPAUSED(int ms) { invoke<Void>(0x7C496803, ms); } // 0x7C496803
   static Any START_NEW_SCRIPT(Any p0, Any p1) { return invoke<Any>(0x3F166D0E, p0, p1); } // 0x3F166D0E
   static Any START_NEW_SCRIPT_WITH_ARGS(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x4A2100E4, p0, p1, p2, p3); } // 0x4A2100E4
   static void SETTIMERA(Any p0) { invoke<Void>(0x35785333, p0); } // 0x35785333
   static Any TIMESTEP() { return invoke<Any>(0x50597EE2); } // 0x50597EE2
   static void PRINTSTRING(const char* value) { invoke<Void>(0xECF8EB5F, value); } // 0xECF8EB5F
   static void PRINTFLOAT(float value) { invoke<Void>(0xD48B90B6, value); } // 0xD48B90B6
   static void PRINTINT(int value) { invoke<Void>(0x63651F03, value); } // 0x63651F03
   static void PRINTNL() { invoke<Void>(0x868997DA); } // 0x868997DA
   static void PRINTVECTOR(float p0, float p1, float p2) { invoke<Void>(0x85F31FB, p0, p1, p2); } // 0x85F31FB
   static float SQRT(float value) { return invoke<float>(0x145C7701, value); } // 0x145C7701
   static float POW(float base, float exponent) { return invoke<float>(0x85D134F8, base, exponent); } // 0x85D134F8
   static Any EXP(Any p0, Any p1) { return invoke<Any>(0xE2313450, p0, p1); } // 0xE2313450
   static float VMAG(float p0, float p1, float p2) { return invoke<float>(0x1FCF1ECD, p0, p1, p2); } // 0x1FCF1ECD
   static float VDIST(float x1, float y1, float z1, float x2, float y2, float z2) { return invoke<float>(0x3C08ECB7, x1, y1, z1, x2, y2, z2); } // 0x3C08ECB7
   static float VDIST2(float x1, float y1, float z1, float x2, float y2, float z2) { return invoke<float>(0xC85DEF1F, x1, y1, z1, x2, y2, z2); } // 0xC85DEF1F
   static int SHIFT_LEFT(int value, int bitShift) { return invoke<int>(0x314CC6CD, value, bitShift); } // 0x314CC6CD
   static int SHIFT_RIGHT(int value, int bitShift) { return invoke<int>(0x352633CA, value, bitShift); } // 0x352633CA
   static int FLOOR(float value) { return invoke<int>(0x32E9BE04, value); } // 0x32E9BE04
   static int CEIL(float value) { return invoke<int>(0xD536A1DF, value); } // 0xD536A1DF
   static int ROUND(float value) { return invoke<int>(0x323B0E24, value); } // 0x323B0E24
   static float TO_FLOAT(int value) { return invoke<float>(0x67116627, value); } // 0x67116627
   static void SNAPSHOT_GLOBALS() { invoke<Void>(0x5A25520E); } // 0x5A25520E
   static Any GET_LATEST_CONSOLE_COMMAND(Any p0) { return invoke<Any>(0x2B547FE6, p0); } // 0x2B547FE6
   static Any RESET_LATEST_CONSOLE_COMMAND(Any p0) { return invoke<Any>(0xAA3EC981, p0); } // 0xAA3EC981
   static Any GET_CONSOLE_COMMAND_TOKEN(Any p0) { return invoke<Any>(0x9DE3DE24, p0); } // 0x9DE3DE24
   static Any GET_NUM_CONSOLE_COMMAND_TOKENS(Any p0) { return invoke<Any>(0x608F5BC6, p0); } // 0x608F5BC6
}

namespace ACTOR
{
   static BOOL IS_ACTOR_VALID(Actor actor) { return invoke<BOOL>(0xBA6C3E92, actor); } // 0xBA6C3E92
   static Any GET_ACTORENUM_FROM_STRING(const char* actorName) { return invoke<Any>(0x8B217CAC, actorName); } // 0x8B217CAC
   static BOOL IS_ACTOR_ON_FOOT(Any p0) { return invoke<BOOL>(0x63D6551C, p0); } // 0x63D6551C
   static int _0xB7CE8FCC(Any p0, Any p1, Any p2) { return invoke<int>(0xB7CE8FCC, p0, p1, p2); } // 0xB7CE8FCC
   static int _0xB89CC342(Any p0, Any p1, Any p2) { return invoke<int>(0xB89CC342, p0, p1, p2); } // 0xB89CC342
   static int ACTORS_IN_RANGE(Any p0, Any p1, Any p2) { return invoke<int>(0x50A3BF5D, p0, p1, p2); } // 0x50A3BF5D
   static Any GET_ACTOR_VELOCITY(Actor actor, Any* p1, Any* p2, Any* p3) { return invoke<Any>(0xAD6AF65C, actor, p1, p2, p3); } // 0xAD6AF65C
   static float GET_ACTOR_HEIGHT(Actor actor) { return invoke<float>(0xE173CE48, actor); } // 0xE173CE48
   static int* _0xAB8A1C15(float p0) { return invoke<int*>(0xAB8A1C15, p0); } // 0xAB8A1C15 ->(RIENS001, 15)
   static const char* _0xDAD46FAB() { return invoke<const char*>(0xDAD46FAB); }// 0xDAD46FAB ->(RIENS001, 15)
   static int _ACTOR_IN_WORLD(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0xA2DEC153, p0, p1, p2, p3, p4, p5); } // 0xA2DEC153 
   static BOOL IS_AREA_OBSTRUCTED(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<BOOL>(0x5F655C68, p0, p1, p2, p3, p4, p5); } // 0x5F655C68
   static BOOL _0x0733E811(float p0, float p1, float p2, float p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<BOOL>(0x0733E811, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x0733E811
   static int GET_ACTORENUM_SPECIES(Any p0) { return invoke<int>(0x6AC01FCB, p0); } // 0x6AC01FCB
   static int _GET_ACTOR_BASE_TYPE(Any p0) { return invoke<int>(0xEE0AB3DD, p0); } // 0xEE0AB3DD
   static int _GET_ACTOR_ENUM_AVATAR_GROUP(Any p0) { return invoke<int>(0x6AFF3122, p0); } // 0x6AFF3122
   static int _GET_MP_ANIM_SET_NAME(Any p0) { return invoke<int>(0x7D397CAA, p0); } // 0x7D397CAA
   static int DECOR_HANDLES_RELATIVE(Any p0) { return invoke<int>(0x8DAC4359, p0); } // 0x8DAC4359
   static int SET_ACTOR_STAMINA(Any p0, float p1) { return invoke<int>(0xDE0B9673, p0, p1); } // 0xDE0B9673
   static int GET_ACTOR_GAIT_TYPE(Any p0) { return invoke<int>(0xAC232F6E, p0); } // 0xAC232F6E
   static Any GET_ACTOR_POSTURE(Any p0) { return invoke<Any>(0xDB993A4F, p0); } // 0xDB993A4F
   static void SET_ACTOR_POSTURE(Actor actor, Any p1) { invoke<Void>(0x708D9BD3, actor, p1); }	// 0x708D9BD3
   static int _0xDCC91F8C(Any p0, const char* p1) { return invoke<int>(0xDCC91F8C, p0, p1); } // 0xDCC91F8C
   static Any GET_ACTOR_TYPE(Any p0) { return invoke<Any>(0xABFD3560, p0); } // 0xABFD3560
   static BOOL IS_ACTOR_MALE(Any p0) { return invoke<BOOL>(0x2091F142, p0); } // 0x2091F142
   static void SET_ACTOR_SEX(Actor actor, Any p1) { invoke<Void>(0x9C42B7A2, actor, p1); } // 0x9C42B7A2
   static void SET_ACTOR_IS_COMPANION(Actor actor, Any p1) { invoke<Void>(0x4C94EB9E, actor, p1); } // 0x4C94EB9E
   static void SET_ACTOR_IS_THE_BEASTMASTER(Actor actor, Any p1) { invoke<Void>(0x8392855D, actor, p1); } // 0x8392855D
   static void SET_ACTOR_TIME_OF_LAST_CRIME(Actor actor, Any p1) { invoke<Void>(0xE9D86A7A, actor, p1); } // 0xE9D86A7A
   static int _0x2CB5D7AF() { return invoke<int>(0x2CB5D7AF); } // 0x2CB5D7AF
   static BOOL IS_PLAYER_WEAPON_ZOOMED(Any p0) { return invoke<BOOL>(0x0A842786, p0); } // 0x0A842786
   static BOOL IS_ACTOR_ANIMAL(Actor actor) { return invoke<BOOL>(0x8E0769F3, actor); } // 0x8E0769F3
   static BOOL IS_ACTOR_CROUCHING(Any p0) { return invoke<BOOL>(0xF6BF4242, p0); } // 0xF6BF4242
   static BOOL IS_ACTOR_FLYING(Actor actor) { return invoke<BOOL>(0x25670955, actor); } // 0x25670955
   static BOOL IS_ACTOR_HUMAN(Actor actor) { return invoke<BOOL>(0x882C84DC, actor); } // 0x882C84DC
   static BOOL IS_ACTOR_JUMPING(Actor actor) { return invoke<BOOL>(0xDFF96719, actor); } // 0xDFF96719
   static BOOL IS_ACTOR_SHOOTING(Actor actor) { return invoke<BOOL>(0x4B441DC4, actor); } // 0x4B441DC4
   static BOOL IS_ACTOR_BLINDFIRING(Any p0) { return invoke<BOOL>(0x6396ABB7, p0); } // 0x6396ABB7
   static BOOL IS_ACTOR_RELOADING(Any p0) { return invoke<BOOL>(0x39C518DB, p0); } // 0x39C518DB
   static BOOL IS_ACTOR_THROWING(Actor actor) { return invoke<BOOL>(0x886BD8AD, actor); } // 0x886BD8AD
   static BOOL IS_ACTOR_WHISTLING(Any p0) { return invoke<BOOL>(0x3612AC73, p0); } // 0x3612AC73
   static BOOL IS_ACTOR_ON_LADDER(Any p0) { return invoke<BOOL>(0xE975BE40, p0); } // 0xE975BE40
   static BOOL _0xE27EBCBD(Any p0) { return invoke<BOOL>(0xE27EBCBD, p0); } // 0xE27EBCBD
   static void SUSPEND_MOVER(Any p0) { invoke<Void>(0x017D270E, p0); } // 0x017D270E
   static void ENABLE_MOVER(Any p0) { invoke<Void>(0xE29F0A39, p0); } // 0xE29F0A39
   static void SET_MOVER_FROZEN(Any p0, Any p1) { invoke<Void>(0x13E6B5EE, p0, p1); } // 0x13E6B5EE
   static BOOL IS_MOVER_FROZEN(Any p0) { return invoke<BOOL>(0x9C12BD5A, p0); } // 0x9C12BD5A
   static int _SET_USE_COARSE_BOUNDS(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x63925367, p0, p1, p2, p3); } // 0x63925367
   static int _SUPPRESS_MOVE_COLLISIONS(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x61664EC0, p0, p1, p2, p3); } // 0x61664EC0
   static BOOL IS_ACTOR_ON_GROUND(Actor actor) { return invoke<int>(0x709EC06C, actor); } // 0x709EC06C
   static BOOL IS_ACTOR_ON_PATH(Actor actor, Any p1, Any p2, Any p3, Any p4) { return invoke<BOOL>(0x8ED9DAFC, actor, p1, p2, p3, p4); } // 0x8ED9DAFC
   static int _IS_MOVER_ON_VEHICLE_PATH(Actor actor, Any p1, Any p2, Any p3, Any p4) { return invoke<BOOL>(0x4A2DE1D0, actor, p1, p2, p3, p4); } // 0x4A2DE1D0
   static BOOL IS_ACTOR_IN_WATER(Any p0) { return invoke<BOOL>(0x7D65D9C7, p0); } // 0x7D65D9C7
   static BOOL _IS_ACTOR_IN_WATER_OF_DEPTH(Any p0, Any p1, Any p2, Any p3, float p5) { return invoke<int>(0xA6AA7B9E, p0, p1, p2, p3, p5); } // 0xA6AA7B9E
   static int GET_ACTOR_STUCK_STATE(Any p0) { return invoke<int>(0x7B4F9EAC, p0); } // 0x7B4F9EAC
   static int _0xE39E89BD(Any p0) { return invoke<int>(0xE39E89BD, p0); } // 0xE39E89BD
   static BOOL IS_ACTOR_RIDEABLE(Any p0) { return invoke<BOOL>(0x8842C62D, p0); } // 0x8842C62D
   static void SET_ACTOR_RIDEABLE(Actor actor, BOOL p0) { invoke<Void>(0x19F3CB6B, actor, p0); } // 0x19F3CB6B
   static int GET_VEHICLE_BUMP_COUNT(Any p0) { return invoke<int>(0x04CF7C3E, p0); } // 0x04CF7C3E
   static void RESET_VEHICLE_BUMP_COUNT(Any p0) { invoke<Void>(0x0E9BA223, p0); } // 0x0E9BA223
   static int _SET_CUSTOM_ANIM_SPEED_SCALE(Any p0) { return invoke<int>(0x5FEA3E61, p0); } // 0x5FEA3E61
   static Any ACTOR_RESET_ANIMS(Any p0, Any p1) { return invoke<Any>(0x35D8B4AA, p0, p1); } // 0x35D8B4AA
   static int _0x817B6952(Any p0) { return invoke<int>(0x817B6952, p0); } // 0x817B6952
   static int _0x4A1D2E25(Any p0) { return invoke<int>(0x4A1D2E25, p0); } // 0x4A1D2E25
   static int _0xC17BAD12(Any p0) { return invoke<int>(0xC17BAD12, p0); } // 0xC17BAD12
   static int _0x0B5E1904(Any p0, Any p1) { return invoke<int>(0x0B5E1904, p0, p1); } // 0x0B5E1904
   static int _0x50ED77F1(Any p0, Any p1) { return invoke<int>(0x50ED77F1, p0, p1); }// 0x50ED77F1
   static void ACTOR_ENABLE_VARIABLE_MESH(Any p0, Any p1, Any p2) { invoke<Void>(0xDA2F6203, p0, p1, p2); } // 0xDA2F6203
   static int ACTOR_IS_VARIABLE_MESH_ENABLED(Any p0, Any p1) { return invoke<int>(0x5DE31288, p0, p1); } // 0x5DE31288
   static void ACTOR_SET_GRABBED_BY_CUTSCENE(Any p0, Any p1) { invoke<Void>(0x6D3E430D, p0, p1); } // 0x6D3E430D
   static int ACTOR_IS_GRABBED_BY_CUTSCENE(Actor actor) { return invoke<int>(0x776999DB, actor); } // 0x776999DB
   static BOOL ACTOR_IS_HIDDEN_BY_CUTSCENE(Any p0) { return invoke<BOOL>(0x488C95C4, p0); } // 0x488C95C4
   static BOOL _IS_ACTOR_FULLY_FADED(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<BOOL>(0x0CC3D8F6, p0, p1, p2, p3, p4); } // 0x0CC3D8F6
   static int SET_ACTOR_HEARING_MAX_RANGE(Any p0, Any p1) { return invoke<int>(0x55AACDFD, p0, p1); } // 0x55AACDFD
   static float GET_ACTOR_VISION_FIELD_OF_VIEW(Any p0) { return invoke<float>(0x21CE712F, p0); } // 0x21CE712F
   static int SET_ACTOR_VISION_FIELD_OF_VIEW(Any p0, Any p1) { return invoke<int>(0xF8F3FE84, p0, p1); } // 0xF8F3FE84
   static int GET_ACTOR_VISION_MAX_RANGE(Any p0) { return invoke<int>(0x4A4B4B26, p0); } // 0x4A4B4B26
   static int SET_ACTOR_VISION_MAX_RANGE(Any p0, Any p1, Any p2) { return invoke<int>(0x4E3E9B70, p0, p1, p2); } // 0x4E3E9B70
   static int GET_ACTOR_VISION_MAX_RANGE_2(float p0) { return invoke<int>(0x5C8DD257, p0); } // 0x5C8DD257
   static int SET_ACTOR_VISION_XRAY(Any p0, Any p1) { return invoke<int>(0x8D5175A8, p0, p1); } // 0x8D5175A8
   static int GET_ACTOR_VISION_XRAY(Any p0) { return invoke<int>(0xBFABD82E, p0); } // 0xBFABD82E
   static int _0xAAC96EFF(Any p0, Any p1) { return invoke<int>(0xAAC96EFF, p0, p1); } // 0xAAC96EFF
   static BOOL _0x9CD3385E(Any p0) { return invoke<BOOL>(0x9CD3385E, p0); } // 0x9CD3385E
   static int _ACTOR_ALLOW_BUMP_REACTIONS(Actor actor, BOOL toggle) { return invoke<int>(0xC52B5F18, actor, toggle); } // 0xC52B5F18
   static int _0xEB7B0FAA(Any p0, Any p1) { return invoke<int>(0xEB7B0FAA, p0, p1); } // 0xEB7B0FAA
   static void SET_RCM_ACTOR_CALL_OVER_ENABLE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0x2C6A5FAC, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x2C6A5FAC
   static void SET_RCM_WAS_JOHN_NOW_JACK(Any p0, Any p1) { invoke<Void>(0xE4AA7B35, p0, p1); } // 0xE4AA7B35
   static int* _0xD15B53F8(float p0) { return invoke<int*>(0xD15B53F8, p0); } // 0xD15B53F8
   static int _SET_ALLOW_PLAYER_GREET_RESPONSES(Any p0) { return invoke<int>(0xC28A5950, p0); } // 0xC28A5950
   static void SET_ACTOR_ALLOW_WEAPON_REACTIONS(Actor actor, Any p1) { invoke<Void>(0x003D7C2F, actor, p1); } // 0x003D7C2F
   static void SET_ACTOR_ALLOW_WEAPON_REACTION_FLEE(Any p0, Any p1) { invoke<Void>(0xBAF9D599, p0, p1); } // 0xBAF9D599
   static int GET_ACTOR_WEAPON_REACTION_ACTOR_TYPE(Actor p0) { return invoke<int>(0x78B7976E, p0); } // 0x78B7976E
   static void SET_ACTOR_WEAPON_REACTION_ACTOR_TYPE(Any p0, Any p1) { invoke<Void>(0x18BA1216, p0, p1); } // 0x18BA1216
   static int SET_PLAYER_CAUSE_WEAPON_REACTIONS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return invoke<int>(0x0634B4D1, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x0634B4D1
   static void SET_ACTOR_WEAPON_REACTION_NO_FLEE_HACK(Any p0, Any p1) { invoke<Void>(0xD9934D6E, p0, p1); } // 0xD9934D6E
   static int SET_ACTOR_OBSERVED_TARGETED_REACTIONS(Any p0, Any p1) { return invoke<int>(0x0A23F215, p0, p1); } // 0x0A23F215
   static void SET_PLAYER_CAUSE_WEAPON_REACTION_COMBAT(Any p0, Any p1) { invoke<Void>(0xFFDA2D88, p0, p1); } // 0xFFDA2D88
   static int SET_ACTOR_REACT_TO_LASSO(Any p0, const char* p1) { return invoke<int>(0x7B7D1742, p0, p1); } // 0x7B7D1742
   static int SET_ACTOR_ALLOW_DISARM(Any p0, const char* p1) { return invoke<int>(0x76A72D9A, p0, p1); } // 0x76A72D9A
   static void SET_ANIMAL_CAN_ATTACK(Any p0, Any p1) { invoke<Void>(0x2B403538, p0, p1); } // 0x2B403538
   static Any GET_CURRENT_GRINGO(Any p0) { return invoke<Any>(0x5D9DB7A5, p0); } // 0x5D9DB7A5
   static int _SET_GRINGO_RESTRICTION(Any p0) { return invoke<int>(0x527CB774, p0); }  // 0x527CB774
   static int _SET_GRINGO_RESTRICTION_2(Any p0) { return invoke<int>(0x660DBDDD, p0); } // 0x660DBDDD
   static int _0xF04335A6(Any p0, Any p1) { return invoke<int>(0xF04335A6, p0, p1); } // 0xF04335A6
   static BOOL _0xFB2B0CCF(Any p0) { return invoke<int>(0xFB2B0CCF, p0); } // 0xFB2B0CCF
   static void REPORT_GRINGO_USE_PHASE(Any p0, Any p1) { invoke<Void>(0xA41B161C, p0, p1); } // 0xA41B161C
   static int _0x9028B082() { return invoke<int>(0x9028B082); } // 0x9028B082
   static int CAN_PLAYER_DIE() { return invoke<int>(0x90F9555B); } // 0x90F9555B
   static void CLEAR_ACTOR_MAX_SPEED(Any p0) { invoke<Void>(0xA9691E66, p0); } // 0xA9691E66
   static void SET_ACTOR_MAX_SPEED(Any p0, Any p1) { invoke<Void>(0x9CB01B27, p0, p1); } // 0x9CB01B27
   static void SET_ACTOR_MAX_SPEED_ABSOLUTE(Any p0, Any p1) { invoke<Void>(0x950B8870, p0, p1); } // 0x950B8870
   static void CLEAR_ACTOR_MIN_SPEED(Any p0) { invoke<Void>(0x036D75D5, p0); } // 0x036D75D5
   static void SET_ACTOR_MIN_SPEED(Any p0, Any p1) { invoke<Void>(0xA854EE99, p0, p1); } // 0xA854EE99
   static int SET_ACTOR_MIN_SPEED_ABSOLUTE(Any p0, float p1) { return invoke<int>(0x04D4A734, p0, p1); } // 0x04D4A734
   static int GET_ACTOR_MAX_SPEED(Any p0) { return invoke<int>(0x627E52EA, p0); } // 0x627E52EA
   static int GET_ACTOR_MAX_SPEED_ABSOLUTE(Any p0) { return invoke<int>(0x56DE7F21, p0); } // 0x56DE7F21
   static int GET_ACTOR_MIN_SPEED(Any p0) { return invoke<int>(0x8D0DCEB6, p0); } // 0x8D0DCEB6
   static void GET_ACTOR_MIN_SPEED(Any p0, Any p1) { invoke<Void>(0x8D0DCEB6, p0, p1); } // 0x09D78931
   static void CLEAR_LAST_ATTACK(Any p0) { invoke<Void>(0x68D4A021, p0); } // 0x68D4A021
   static int _0xEB40C2FC(Any p0, Any p1) { return invoke<int>(0xEB40C2FC, p0, p1); } // 0xEB40C2FC
   static float _0x69FA5315(Any p0) { return invoke<float>(0x69FA5315, p0); } // 0x69FA5315
   static float _0x8C221B4D(Any p0) { return invoke<float>(0x8C221B4D, p0); }// 0x8C221B4D
   static int GET_ACTOR_COMBAT_CLASS(Any p0) { return invoke<int>(0x0129B715, p0); } // 0x0129B715
   static int _0x8062BD74(Any p0, Any p1, float p2) { return invoke<int>(0x8062BD74, p0, p1, p2); } // 0x8062BD74
   static Any BEGIN_DUEL(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12) { return invoke<Any>(0x44B7FF7E, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 0x44B7FF7E
   static Any CANCEL_DUEL(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0x4E86F0B5, p0, p1, p2, p3, p4); } // 0x4E86F0B5
   static int ADD_DUEL_HOSTAGE(Any p0, Any p1) { return invoke<int>(0x82A6B8FC, p0, p1); } // 0x82A6B8FC
   static int GET_CURRENT_DUEL_SCORE(Any p0) { return invoke<int>(0x33CE5435, p0); } // 0x33CE5435
   static int SET_DUEL_DIFFICULTY(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x3E5C3C2D, p0, p1, p2, p3); } // 0x3E5C3C2D
   static int _0x8007587C(Any p0) { return invoke<int>(0x8007587C, p0); } // 0x8007587C
   static void SET_ACTOR_EXEMPT_FROM_AMBIENT_RESTRICTIONS(Any p0, Any p1) { invoke<Void>(0x4D0A87BF, p0, p1); } // 0x4D0A87BF
   static int _0x6695E185(Any p0) { return invoke<int>(0x6695E185, p0); } // 0x6695E185
   static int _0x29AEB2DB(Any p0) { return invoke<int>(0x29AEB2DB, p0); } // 0x29AEB2DB
   static int _0xD3D8E8ED(Any p0) { return invoke<int>(0xD3D8E8ED, p0); } // 0xD3D8E8ED
   static float _0x2B8C3258(Any p0) { return invoke<float>(0x2B8C3258, p0); } // 0x2B8C3258
   static int NET_SET_NODE_REPLICATION(Any p0, Any p1, Any p2) { return invoke<int>(0xA4B5275C, p0, p1, p2); } // 0xA4B5275C
   static void SET_ACTOR_ACTION_SIGNAL(Any p0, Any p1, Any p2) { invoke<Void>(0x382E7CCC, p0, p1, p2); } // 0x382E7CCC
   static void TOGGLE_ACTOR_ACTION_SIGNAL_ON(Any p0, Any p1, Any p2) { invoke<Void>(0x415F9BC3, p0, p1, p2); } // 0x415F9BC3
   static void TOGGLE_ACTOR_ACTION_SIGNAL_OFF(Any p0) { invoke<Void>(0x4F605632, p0); } // 0x4F605632
   static int _0x02365961(Any* p0, Any p1) { return invoke<int>(0x02365961, p0, p1); } // 0x02365961
   static int _0xD079EB62(Any p0, Any p1) { return invoke<int>(0xD079EB62, p0, p1); } // 0xD079EB62
   static void SET_ACTOR_AUTO_TRANSITION_TO_DRIVER_SEAT(Any p0, Any p1) { invoke<Void>(0x47930AA4, p0, p1); } // 0x47930AA4
   static int SET_ACTOR_FLY_FX(Any p0, Any p1) { return invoke<int>(0xEDC806BA, p0, p1); } // 0xEDC806BA
   static void SET_ACTOR_MOVE_CONFLICT_HIGH_PRIORITY(Any p0, Any p1) { invoke<Void>(0x7A746D3A, p0, p1); } // 0x7A746D3A
   static void SET_ACTOR_MOVE_CONFLICT_ALLOWED_TO_RUN_OVER_SMALL_ANIMALS(Any p0, Any p1) { invoke<Void>(0x32CB0E86, p0, p1); } // 0x32CB0E86
   static void SET_ACTOR_IS_AMBIENT(Any p0, Any p1) { invoke<Void>(0x4CB24141, p0, p1); } // 0x4CB24141
   static void SET_ACTOR_IS_SHOPKEEPER(Any p0, Any p1, Any p2) { invoke<Void>(0x0880DBF5, p0, p1, p2); } // 0x0880DBF5
   static void SET_ACTOR_SHOULD_TAUNT(Any p0, Any p1) { invoke<Void>(0x199600FA, p0, p1); } // 0x199600FA
   static void SET_ACTOR_CAN_BUMP(Any p0, Any p1) { invoke<Void>(0xB9744BE7, p0, p1); } // 0xB9744BE7
   static int SET_ACTOR_MAX_FRESHNESS(Any p0, Any p1) { return invoke<int>(0xBADB24FB, p0, p1); } // 0xBADB24FB
   static int GET_ACTOR_MAX_FRESHNESS(Any p0) { return invoke<int>(0xF1D2A13E, p0); } // 0xF1D2A13E
   static void MAKE_BIRD_FLY_FROM_POINT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x5E54E254, p0, p1, p2, p3, p4, p5, p6); } // 0x5E54E254
}

namespace ACTORDRAW
{
   static void SET_DRAW_ACTOR(Any p0) { invoke<Void>(0xE6644CE5, p0); } // 0xE6644CE5
   static Any GET_DRAW_ACTOR(Any p0) { return invoke<Any>(0x085A9CA6, p0); } // 0x085A9CA6
}

namespace ACTORENUM
{
   static int _0xD02757C1(Any p0, Any p1) { return invoke<int>(0xD02757C1, p0, p1); } // 0xD02757C1
   static int* _0x886E06C2(Any p0, const char* p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int*>(0x886E06C2, p0, p1, p2, p3, p4, p5); } // 0x886E06C2
   static int* _0xB6839756() { return invoke<int*>(0xB6839756); } // 0xB6839756
   static const char* _0xCB139D15(Any p0) { return invoke<const char*>(0xCB139D15, p0); } // 0xCB139D15
   static int _0xF07F5E41() { return invoke<int>(0xF07F5E41); } // 0xF07F5E41 Unused
}

namespace ACTORINFO
{
   static Any GET_LAST_ATTACKER(Any p0) { return invoke<Any>(0x2C0F211D, p0); } // 0x2C0F211D
   static Any GET_LAST_HIT_TIME(Any p0) { return invoke<Any>(0x3A207AF2, p0); } // 0x3A207AF2
   static Any GET_LAST_HIT_WEAPON(Any p0) { return invoke<Any>(0x07B7AA6B, p0); } // 0x07B7AA6B
   static Any GET_LAST_HIT_FLAGS(Any p0) { return invoke<Any>(0x08308EBA, p0); } // 0x08308EBA
   static Any GET_LAST_DAMAGE(Any p0) { return invoke<Any>(0x45556269, p0); } // 0x45556269
   static Any GET_LAST_HIT_ZONE(Any p0, Any* p1) { return invoke<Any>(0x855F9A3B, p0, p1); } // 0x855F9A3B
   static Any _0x4747F219() { return invoke<Any>(0x4747F219); } // 0x4747F219
   static Any _0xF75FE17F() { return invoke<Any>(0xF75FE17F); } // 0xF75FE17F
   static Any CLEAR_LAST_HIT() { return invoke<Any>(0x8D696237); } // 0x8D696237
   static void KILL_ACTOR(Actor actor) { invoke<Void>(0x8B08ECA2, actor); } // 0x8B08ECA2
   static void _0x6085F7AC(Any p0, Any p1) { invoke<Void>(0x6085F7AC, p0, p1); } // 0x6085F7AC
   static BOOL IS_ACTOR_ALIVE(Actor actor) { return invoke<BOOL>(0x2F232639, actor); } // 0x2F232639
   static BOOL IS_ACTOR_DEAD(Actor actor) { return invoke<BOOL>(0x0D798FFE, actor); } // 0x0D798FFE
   static BOOL IS_ACTOR_RAGDOLL(Actor actor) { return invoke<BOOL>(0x3918D335, actor); } // 0x3918D335
   static void SET_ACTOR_HEALTH(Actor actor, float health) { invoke<Void>(0xFA090024, actor, health); } // 0xFA090024
   static float GET_ACTOR_HEALTH(Actor actor) { return invoke<float>(0xF246F15D, actor); } // 0xF246F15D
   static float GET_ACTOR_MAX_HEALTH(Actor actor) { return invoke<float>(0xB69A84AF, actor); } // 0xB69A84AF
   static void SET_ACTOR_MAX_HEALTH(Actor actor, Any p1) { invoke<Void>(0x165BD4C5, actor, p1); } // 0x165BD4C5
   static Any _0x7A207FFE(Any p0) { return invoke<Any>(0x7A207FFE, p0); } // 0x7A207FFE
   static void _SET_ACTOR_HEALTH_2(Actor actor, Any p1) { invoke<Void>(0x3A2D7759, actor, p1); } // 0x3A2D7759
   static Any _GET_ACTOR_HEALTH_2(Actor actor) { return invoke<Any>(0x44787A58, actor); } // 0x44787A58
   static Any GET_ACTOR_MAX_KO_POINTS(Actor actor) { return invoke<Any>(0xAFC96669, actor); } // 0xAFC96669
   static void _SET_ACTOR_HEALTH_3(Actor actor, Any p1) { invoke<Void>(0x4EEC6628, actor, p1); } // 0x4EEC6628
   static void _SET_ACTOR_HEALTH_4(Actor actor, Any p1) { invoke<Void>(0x479B997B, actor, p1); } // 0x479B997B
   static BOOL IS_ACTOR_DRUNK(Actor actor) { return invoke<BOOL>(0xFF07D58C, actor); } // 0xFF07D58C
   static void SET_ACTOR_DRUNK(Actor actor, BOOL toggle) { invoke<Void>(0x9F57742C, actor, toggle); } // 0x9F57742C
   static void SET_ACTOR_PASSED_OUT(Actor actor, Any p1) { invoke<Void>(0x2A9FD09F, actor, p1); } // 0x2A9FD09F
   static void SET_ACTOR_HANGING_FROM_NOOSE(Actor actor, Any p1) { invoke<Void>(0x5262C0F7, actor, p1); } // 0x5262C0F7
   static void _0x6287203C(Any p0) { invoke<Void>(0x6287203C, p0); } // 0x6287203C
   static void _0x1082715D() { invoke<Void>(0x1082715D); } // 0x1082715D
}

namespace ACTORSET
{
   static int _CREATE_SET_ACTORSET(Any p0, Any p1, Any p2) { return invoke<int>(0x009DFC82, p0, p1, p2); } // 0x009DFC82
   static BOOL IS_ACTORSET_VALID(Any p0) { return invoke<BOOL>(0x76E8975E, p0); } // 0x76E8975E
   static Any FIND_NAMED_ACTORSET(Any p0) { return invoke<Any>(0x5454B159, p0); } // 0x5454B159
   static void DESTROY_ACTORSET(Any p0, Any p1) { invoke<Void>(0x147A0BEE, p0, p1); } // 0x147A0BEE
   static int DISBAND_ACTORSET(Any p0) { return invoke<int>(0x2739F04D, p0); } // 0x2739F04D
   static Any ADD_ACTORSET_MEMBER(Any p0, Any p1) { return invoke<Any>(0xE09DB6C1, p0, p1); } // 0xE09DB6C1
   static int REMOVE_ACTORSET_MEMBER(Any p0, Any p1) { return invoke<int>(0xD637E449, p0, p1); } // 0xD637E449
   static BOOL IS_ACTOR_IN_ACTORSET(Any p0, Any p1) { return invoke<BOOL>(0xC6FE68DF, p0, p1); } // 0xC6FE68DF
   static Any GET_ACTOR_FROM_ACTORSET(Any p0) { return invoke<Any>(0xC5202810, p0); } // 0xC5202810
   static Any GET_ACTORSET_SIZE(Any p0) { return invoke<Any>(0xA24F4799, p0); } // 0xA24F4799
}

namespace AI
{
   static void AI_BEHAVIOR_SET_ALLOW(Any p0, Any p1, Any p2) { invoke<Void>(0x4A69F264, p0, p1, p2); } // 0x4A69F264
   static BOOL AI_ACTION_IS_ACTIVE(Any p0, const char* p1) { return invoke<BOOL>(0x8F428EDF, p0, p1); } // 0x8F428EDF
   static int AI_GOAL_AIM_AT_COORD(Any p0, Any p1, const char* p2) { return invoke<int>(0x671851D4, p0, p1, p2); } // 0x671851D4
   static void AI_GOAL_AIM_AT_OBJECT(Any p0, Any p1, Any p2) { invoke<Void>(0x3CD232B2, p0, p1, p2); } // 0x3CD232B2
   static void AI_GOAL_AIM_CLEAR(Any p0) { invoke<Void>(0xD5100DC2, p0); } // 0xD5100DC2
   static void AI_GOAL_LOOK_AT_ACTOR(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x96928D25, p0, p1, p2, p3, p4, p5, p6); } // 0x96928D25
   static void AI_GOAL_LOOK_AT_COORD(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xB162690D, p0, p1, p2, p3, p4, p5); } // 0xB162690D
   static int _0x15B7044B(Any p0, Any p1, float p2) { return invoke<int>(0x15B7044B, p0, p1, p2); } // 0x15B7044B
   static int _0x245D0CFD(Any p0) { return invoke<int>(0x245D0CFD, p0); } // 0x245D0CFD
   static void AI_GOAL_LOOK_AT_NEUTRAL(Any p0, Any p1) { invoke<Void>(0x8456676E, p0, p1); } // 0x8456676E
   static void AI_GOAL_LOOK_CLEAR(Any p0) { invoke<Void>(0x6AF3E54E, p0); } // 0x6AF3E54E
   static int AI_GOAL_SHOOT_AT_OBJECT(Any p0, Any p1) { return invoke<int>(0x10674B4F, p0, p1); } // 0x10674B4F
   static void AI_GOAL_SHOOT_AT_COORD(Any p0, Any p1) { invoke<Void>(0x6C65E46E, p0, p1); } // 0x6C65E46E
   static void AI_GOAL_SHOOT_CLEAR(Any p0) { invoke<Void>(0xC43A9268, p0); } // 0xC43A9268
   static int AI_GOAL_STAND_AT_COORD(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xD9B27A9E, p0, p1, p2, p3); } // 0xD9B27A9E
   static int AI_GOAL_STAND_CLEAR(Any p0) { return invoke<int>(0xEADB58EB, p0); } // 0xEADB58EB
   static int _AI_GOAL_FAILED_TO_LOOK_UP_PREDICATE(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x31D76951, p0, p1, p2, p3, p4); } // 0x31D76951
   static BOOL _0x1FEECD4C(Any p0) { return invoke<BOOL>(0x1FEECD4C, p0); } // 0x1FEECD4C
   static void AI_PREDICATE_OVERRIDE_CLEAR(Any p0, Any p1) { invoke<Void>(0x1A137442, p0, p1); } // 0x1A137442
   static void AI_PREDICATE_OVERRIDE_CLEAR_ALL(Any p0) { invoke<Void>(0x3CAC2441, p0); } // 0x3CAC2441
   static void AI_PREDICATE_OVERRIDE_SET_BOOL(Any p0, Any p1, Any p2) { invoke<Void>(0x1117C85A, p0, p1, p2); } // 0x1117C85A
   static Any AI_IGNORE_ACTOR(Any p0, Any p1) { return invoke<Any>(0x8D1FC73C, p0, p1); } // 0x8D1FC73C
   static int _0x98790639(Any p0) { return invoke<int>(0x98790639, p0); } // 0x98790639
   static int _0x4DF3C5D1() { return invoke<int>(0x4DF3C5D1); } // 0x4DF3C5D1
   static int _0xB421AFCA(Any p0) { return invoke<int>(0xB421AFCA, p0); } // 0xB421AFCA
   static int _0xA737CCAC(Any p0) { return invoke<int>(0xA737CCAC, p0); } // 0xA737CCAC
   static Any _0xBE17EB88(Any p0) { return invoke<Any>(0xBE17EB88, p0); } // 0xBE17EB88
   static Any _0xABC78721(Any p0) { return invoke<Any>(0xABC78721, p0); } // 0xABC78721
   static int AI_SHOOT_TARGET_CLEAR_OFFSET(Any p0) { return invoke<int>(0x548541C1, p0); } // 0x548541C1
   static int AI_SHOOT_TARGET_SET_OFFSET(Any p0, Any p1) { return invoke<int>(0x039C69C4, p0, p1); } // 0x039C69C4
   static void AI_SHOOT_TARGET_SET_BONE(Any p0, Any p1, Any p2) { invoke<Void>(0x47C2C7B0, p0, p1, p2); } // 0x47C2C7B0
   static int _0xFF36BAED(Any p0, Any p1, float p2) { return invoke<int>(0xFF36BAED, p0, p1, p2); } // 0xFF36BAED
   static int _0x6F37F42C(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x6F37F42C, p0, p1, p2, p3); } // 0x6F37F42C
   static BOOL _0xA90A13A5(Any p0, BOOL p1) { return invoke<BOOL>(0xA90A13A5, p0, p1); } // 0xA90A13A5
   static BOOL _0xF0511878(BOOL p0) { return invoke<BOOL>(0xF0511878, p0); } // 0xF0511878
   static int _0xE56D3FCE(Any p0, Any p1, float p2) { return invoke<int>(0xE56D3FCE, p0, p1, p2); } // 0xE56D3FCE
   static int _AI_GOAL_LOOK_AT_ACTOR_TO_STOP_LOOKING_AT_COORDINATE(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x6C194C1F, p0, p1, p2, p3); } // 0x6C194C1F
   static int _AI_GOAL_LOOK_AT_ACTOR_ANOTHER_ACTOR(Any p0, Any p1, float p2) { return invoke<int>(0xFE5715A1, p0, p1, p2); } // 0xFE5715A1
   static void SET_AUTO_CONVERSATION_LOOK(Any p0, Any p1) { invoke<Void>(0xA29B9458, p0, p1); } // 0xA29B9458
   static void AI_GOAL_LOOK_AT_PLAYER_WHEN_WITHIN(Any p0, Any p1) { invoke<Void>(0x1F07FC4C, p0, p1); } // 0x1F07FC4C
   static int AI_GOAL_LOOK_AT_PLAYER_WHEN_WITHIN_CLEAR(Any p0) { return invoke<int>(0x4DB11394, p0); } // 0x4DB11394
   static void CLEAR_ACTORS_HORSE(Actor actor) { invoke<Void>(0xFEB74094, actor); } // 0xFEB74094
   static Actor GET_ACTORS_HORSE(Actor actor) { return invoke<Actor>(0x8DDE894F, actor); } // 0x8DDE894F
   static void SET_ACTORS_HORSE(Actor actor, Any p1) { invoke<Void>(0xCFFDF09D, actor, p1); } // 0xCFFDF09D
   static BOOL IS_AI_ACTOR_IN_COMBAT(Any p0) { return invoke<BOOL>(0x08D3CDF9, p0); } // 0x08D3CDF9
   static BOOL IS_AI_ACTOR_PERFORMING_TASK(Any p0) { return invoke<BOOL>(0x6718D199, p0); } // 0x6718D199
   static BOOL IS_AI_ACTOR_UNALERTED(Actor actor) { return invoke<BOOL>(0xC4D114A6, actor); } // 0xC4D114A6
   static void AI_SET_RANGE_ACCURACY_MODIFIER(Any p0, Any p1, Any p2) { invoke<Void>(0x57F96655, p0, p1, p2); } // 0x57F96655
   static void AI_SET_DISARMED(Any p0, Any p1) { invoke<Void>(0x2444577C, p0, p1); } // 0x2444577C
   static int _0xAFB1CC55(Any p0) { return invoke<int>(0xAFB1CC55, p0); } // 0xAFB1CC55
   static int AI_IMPAIRMENT_MASK_MATCHES(Any p0, Any p1) { return invoke<int>(0xB4A15D17, p0, p1); } // 0xB4A15D17
   static void AI_ACTOR_FORCE_SPEED(Actor actor, Any p1) { invoke<Void>(0x70B409D5, actor, p1); } // 0x70B409D5
   static void AI_ACTOR_SET_MATCH_WALK_SPEED_ENABLED(Any p0, Any p1) { invoke<Void>(0x7387772C, p0, p1); } // 0x7387772C
   static void AI_SET_WEAPON_MAX_RANGE(Any p0, Any p1) { invoke<Void>(0xD2BFA6E4, p0, p1); } // 0xD2BFA6E4
   static void AI_SET_WEAPON_MIN_RANGE(Any p0, Any p1) { invoke<Void>(0xE067A925, p0, p1); } // 0xE067A925
   static void AI_SET_WEAPON_DESIRED_RANGE(Any p0, Any p1) { invoke<Void>(0xDA005857, p0, p1); } // 0xDA005857
   static void AI_SET_BURST_DURATION(Any p0, Any p1) { invoke<Void>(0x85F2DF87, p0, p1); } // 0x85F2DF87
   static void AI_SET_BURST_DURATION_RANDOMNESS(Any p0, Any p1) { invoke<Void>(0x9E164C44, p0, p1); } // 0x9E164C44
   static void AI_SET_FIRE_DELAY(Any p0, Any p1) { invoke<Void>(0x05861CF4, p0, p1); } // 0x05861CF4
   static void AI_SET_FIRE_DELAY_RANDOMNESS(Any p0, Any p1) { invoke<Void>(0xC5873149, p0, p1); } // 0xC5873149
   static void AI_SET_SHOTS_PER_BURST(Any p0, Any p1) { invoke<Void>(0xE0172E2D, p0, p1); } // 0xE0172E2D
   static void AI_CLEAR_BURST_DURATION(Any p0) { invoke<Void>(0x01FD4402, p0); } // 0x01FD4402
   static void AI_CLEAR_BURST_DURATION_RANDOMNESS(Any p0) { invoke<Void>(0xCA8EE2A4, p0); } // 0xCA8EE2A4
   static void AI_CLEAR_FIRE_DELAY(Any p0) { invoke<Void>(0xD6886191, p0); } // 0xD6886191
   static void AI_CLEAR_FIRE_DELAY_RANDOMNESS(Any p0) { invoke<Void>(0xE8511960, p0); } // 0xE8511960
   static void AI_CLEAR_SHOTS_PER_BURST(Any p0) { invoke<Void>(0x58A7B2A1, p0); } // 0x58A7B2A1
   static void AI_RESET_FIRING_FSM(Any p0) { invoke<Void>(0x46F51754, p0); } // 0x46F51754
   static void _0xEA2A40BC(Any p0, Any p1) { invoke<Void>(0xEA2A40BC, p0, p1); } // 0xEA2A40BC
   static int AI_IS_HOSTILE_OR_ENEMY(Any p0, Any p1) { return invoke<int>(0x9AB964F4, p0, p1); } // 0x9AB964F4
   static void AI_QUICK_EXIT_GRINGO(Any p0, Any p1) { invoke<Void>(0x6FAF13C2, p0, p1); } // 0x6FAF13C2
   static int AI_IS_AGGROING(Any p0, Any p1) { return invoke<int>(0xC94F9499, p0, p1); } // 0xC94F9499
   static void AI_SET_ALLOWED_MOUNT_DIRECTIONS(Any p0, Any p1) { invoke<Void>(0x7F07210F, p0, p1); } // 0x7F07210F
   static void AI_AVOID_IGNORE_ACTOR(Any p0, Any p1) { invoke<Void>(0x68B268BE, p0, p1); } // 0x68B268BE
   static int AI_AVOID_CLEAR_IGNORE_ACTOR(Any p0) { return invoke<int>(0x1A96EFB9, p0); } // 0x1A96EFB9
   static BOOL IS_AI_ACTOR_ENGAGED_IN_COMBAT(Any p0) { return invoke<BOOL>(0x2DBCB78A, p0); } // 0x2DBCB78A
   static int WAS_AI_ACTOR_PLAYER_WEAPON_THREATENED_BY(Any p0, Any p1, Any p2) { return invoke<int>(0xF5752F72, p0, p1, p2); } // 0xF5752F72
   static void _0x2EBE540D(Any p0, Any p1) { invoke<Void>(0x2EBE540D, p0, p1); } // 0x2EBE540D
   static int AI_GET_IS_RETREATING(Any p0) { return invoke<int>(0x2FABB559, p0); } // 0x2FABB559
   static BOOL AI_HAS_PLAYER_FIRED_GUN_WITHIN(Any p0, float p1) { return invoke<BOOL>(0x1530A3DE, p0, p1); } // 0x1530A3DE
   static int AI_HAS_PLAYER_PROJECTILE_IMPACTED_WITHIN(Any p0, Any p1) { return invoke<int>(0x059F64B8, p0, p1); } // 0x059F64B8
   static int AI_HAS_PLAYER_PROJECTILE_NEAR_MISSED_WITHIN(Any p0, Any p1, Any p2) { return invoke<int>(0xD8574E09, p0, p1); } // 0xD8574E09
   static void AI_SET_PLAYER_PROJECTILE_IMPACT_HEAR_RANGE(Any p0, Any p1) { invoke<Void>(0xDCD2FC0F, p0, p1); } // 0xDCD2FC0F
   static int AI_DONT_SLOW_DOWN_TO_WALK_FOR_TURNS(Any p0, const char* p1) { return invoke<int>(0x0A421F94, p0, p1); } // 0x0A421F94
   static int AI_HAS_ACTOR_BUMPED_INTO_ME(Any p0, Any p1, Any p2) { return invoke<int>(0x6BCC744A, p0, p1, p2); } // 0x6BCC744A
   static int AI_WAS_PUSHED_OVER(Any p0, Any p1) { return invoke<int>(0x09493438, p0, p1); } // 0x09493438
   static BOOL AI_WAS_PUSHED_OVER_BY(Any p0, Any p1, Any p2, Any p3, Any p4, float p5) { return invoke<BOOL>(0x7AF8AFDC, p0, p1, p2, p3, p4, p5); } // 0x7AF8AFDC
   static BOOL AI_SELF_DEFENSE_GET_PLAYER_ATTACKED_FIRST(Any p0) { return invoke<BOOL>(0x04AEE21F, p0); } // 0x04AEE21F
   static int AI_SELF_DEFENSE_GET_ATTACKED_PLAYER_FIRST(Any p0) { return invoke<int>(0x68C50F50, p0); } // 0x68C50F50
   static int AI_SELF_DEFENSE_SET_PLAYER_ATTACKED_FIRST(Any p0) { return invoke<int>(0x0480D5BD, p0); } // 0x0480D5BD
   static int AI_SET_IGNORE_OPEN_AREA_MATERIAL(Any p0, const char* p1) { return invoke<int>(0x902C79A6, p0, p1); } // 0x902C79A6
   static int AI_GET_IGNORE_OPEN_AREA_MATERIAL(Any p0) { return invoke<int>(0x02FBBAD1, p0); } // 0x02FBBAD1
   static int AI_SET_ENABLE_REACTION_VO(Any p0, const char* p1) { return invoke<int>(0x7193449E, p0, p1); } // 0x7193449E
   static int AI_GET_TASK_RETREAT_FLAG(Any p0) { return invoke<int>(0x9B742D25, p0); } // 0x9B742D25
   static void _0x2E5F186B() { invoke<Void>(0x2E5F186B); } // 0x2E5F186B
   static void _0x5C94F6EC(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x5C94F6EC, p0, p1, p2, p3); } // 0x5C94F6EC
   static int AI_HAS_ACTOR_THREATENED_RECENTLY(Any p0) { return invoke<int>(0x5D72FDB6, p0); } // 0x5D72FDB6
   static void _0x06B4A139(Any p0) { invoke<Void>(0x06B4A139, p0); } // 0x06B4A139
   static int AI_SET_TR_PROGRAM_FOR_ACTOR(Any p0, Any p1) { return invoke<int>(0x4D53AC21, p0, p1); } // 0x4D53AC21
}

namespace AI2
{
   static void AI_CLEAR_NAV_MATERIAL_USAGE(Any p0) { invoke<Void>(0x6ADF2927, p0); } // 0x6ADF2927
   static void AI_RESET_NAV_ACTOR_WIDTH(Any p0) { invoke<Void>(0x660C85E5, p0); } // 0x660C85E5
   static void AI_SET_NAV_ACTOR_WIDTH(Any p0, Any p1) { invoke<Void>(0x8404592D, p0, p1); } // 0x8404592D
   static void AI_SET_NAV_HAZARD_AVOIDANCE_ENABLED(Any p0, Any p1, Any p2) { invoke<Void>(0x5D752432, p0, p1, p2); } // 0x5D752432
   static void AI_SET_NAV_MATERIAL_USAGE(Any p0, Any p1, Any p2) { invoke<Void>(0x7B00615F, p0, p1, p2); } // 0x7B00615F
   static void AI_SET_NAV_PATHFINDING_ENABLED(Any p0, Any p1) { invoke<Void>(0x4495F5FC, p0, p1); } // 0x4495F5FC
   static void AI_SET_NAV_PATHFINDING_ENABLED_WHEN_DRIVING(Any p0, Any p1) { invoke<Void>(0x98966941, p0, p1); } // 0x98966941
   static int  AI_SET_NAV_MAX_SLOPE(Any p0, float p1) { return invoke<int>(0xF64D5452, p0, p1); } // 0xF64D5452
   static void AI_SET_NAV_MAX_WATER_DEPTH_LEVEL(Any p0, Any p1) { invoke<Void>(0x29D07F70, p0, p1); } // 0x29D07F70
   static void AI_SET_NAV_ACTOR_AVOIDANCE_MODE(Any p0, Any p1) { invoke<Void>(0x5B483036, p0, p1); }  // 0x5B483036
   static void AI_SET_NAV_ACTOR_AVOIDANCE_ALLOW_TURNS(Any p0, Any p1) { invoke<Void>(0xFCB31704, p0, p1); } // 0xFCB31704
   static int AI_GET_NAV_ACTOR_AVOIDANCE_ALLOW_TURNS(Any p0) { return invoke<int>(0x7C13266C, p0); } // 0x7C13266C
   static void AI_RESET_NAV_SUBGRID_CELL_SIZE(Any p0) { invoke<Void>(0x750A1EF6, p0); } // 0x750A1EF6
   static void AI_SET_NAV_SUBGRID_CELL_SIZE(Any p0, Any p1) { invoke<Void>(0xFF3CEFE2, p0, p1); } // 0xFF3CEFE2
   static void AI_SET_NAV_FAILSAFE_MOVEMENT_ENABLED(Any p0, Any p1) { invoke<Void>(0xC900F0E8, p0, p1); } // 0xC900F0E8
   static int AI_GET_NAV_FAILSAFE_MOVEMENT_ENABLED(Any p0) { return invoke<int>(0xD6F4FDAD, p0); } // 0xD6F4FDAD
   static int AI_SET_NAV_UNALERTED_PREFER_PEDPATH(Any p0, Any p1) { return invoke<int>(0xF1B3072D, p0, p1); } // 0xF1B3072D
   static int AI_SET_NAV_ALLOW_TWEAK_DESIRED_MOVEMENT(Any p0, const char* p1) { return invoke<int>(0xC84EF86B, p0, p1); } // 0xC84EF86B
   static int AI_GET_NAV_ALLOW_TWEAK_DESIRED_MOVEMENT(Any p0) { return invoke<int>(0xBAA2BA4F, p0); } // 0xBAA2BA4F
   static int _0xF435CCDE(Any p0, Any p1) { return invoke<int>(0xF435CCDE, p0, p1); } // 0xF435CCDE
}

namespace AI3
{
   static void DISABLE_VERIFY_SS(Any p0) { invoke<Void>(0x5C580036, p0); } // 0x5C580036
   static void AI_PERCEPTION_SET_VISUAL_ID_DISTANCE(Any p0, Any p1) { invoke<Void>(0x66064774, p0, p1); } // 0x66064774
   static void AI_PERCEPTION_SET_VISUAL_ID_TIME(Any p0, Any p1) { invoke<Void>(0xD786E8C7, p0, p1); } // 0xD786E8C7
   static void AI_DISABLE_PERCEPTION(Any p0) { invoke<Void>(0x8BBB7B12, p0); } // 0x8BBB7B12
   static void AI_ENABLE_PERCEPTION(Any p0) { invoke<Void>(0xAF77C42E, p0); } // 0xAF77C42E
}

namespace AI4
{
   static int AI_RIDING_SET_ATTRIBUTE(Any p0, Any p1, float p2) { return invoke<int>(0x9DDFA9CA, p0, p1, p2); } // 0x9DDFA9CA
   static int _0xF8AFEFA1(Any p1, Any p0) { return invoke<int>(0xF8AFEFA1, p0, p1); } // 0xF8AFEFA1
}

namespace AI5
{
   static int AI_SPEECH_ADD_PHRASE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<int>(0xD269F20B, p0, p1, p2, p3, p4, p5, p6); } // 0xD269F20B
   static void AI_SPEECH_ADD_TAG_FOR_PHRASE(Any p0, Any p1, Any p2) { invoke<Void>(0x15CFAB4C, p0, p1, p2); } // 0x15CFAB4C
   static void AI_SPEECH_REGISTER_EVENT(Any p0, Any p1) { invoke<Void>(0xDD925074, p0, p1); } // 0xDD925074
   static void AI_SPEECH_REGISTER_TAG(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xA08B3E4B, p0, p1, p2, p3); } // 0xA08B3E4B
   static void AI_SPEECH_REGISTER_TAGS_BEGIN(Any p0) { invoke<Void>(0xAB297CCB, p0); } // 0xAB297CCB
   static void AI_SPEECH_REGISTER_TAGS_END() { invoke<Void>(0x90B577F5); } // 0x90B577F5
   static int AI_SPEECH_GET_ALLOW_FOR_ACTOR(Any p0) { return invoke<int>(0xFF0BF292, p0); } // 0xFF0BF292
   static void AI_SPEECH_SET_ALLOW_CONTEXT_FOR_ACTOR(Any p0, Any p1, Any p2) { invoke<Void>(0x6AAB4CD0, p0, p1, p2); } // 0x6AAB4CD0
   static void AI_SPEECH_SET_ALLOW_CONTEXT_GLOBAL(Any p0, Any p1) { invoke<Void>(0x10DDB016, p0, p1); } // 0x10DDB016
   static void AI_SPEECH_SET_ALLOW_FOR_ACTOR(Any p0, Any p1) { invoke<Void>(0x56421F1A, p0, p1); } // 0x56421F1A
   static void DEBUG_PLAYER_LOG(Any p0) { invoke<Void>(0x829F3E70, p0); } // 0x829F3E70
   static int _0xD8C8BEA1(Any p0) { return invoke<int>(0xD8C8BEA1, p0); }// 0xD8C8BEA1
   static int _0x679C5955(Any p0) { return invoke<int>(0x679C5955, p0); } // 0x679C5955
}

namespace ALLOC
{
   static int _FONT_SCALE(Any p0) { return invoke<int>(0x724B4E9B, p0); } // 0x724B4E9B
}

namespace AMBIENT
{
   static void _0xA8ADCAEB(Any p0) { invoke<Void>(0xA8ADCAEB, p0); } // 0xA8ADCAEB
   static void _0xB35C0660(Any p0) { invoke<Void>(0xB35C0660, p0); } // 0xB35C0660
   static int _0xE9C41DFE(float p0) { return invoke<int>(0xE9C41DFE, p0); } // 0xE9C41DFE
   static int _0xB09D5B43() { return invoke<int>(0xB09D5B43); } // 0xB09D5B43
   static BOOL _0x5831679F() { return invoke<BOOL>(0x5831679F); } // 0x5831679F
   static int _0x2CCEA76C(Any p0) { return invoke<int>(0x2CCEA76C, p0); } // 0x2CCEA76C
   static int _0xA607D290() { return invoke<int>(0xA607D290); } // 0xA607D290
   static int _0xC1A30BB5() { return invoke<int>(0xC1A30BB5); } // 0xC1A30BB5
   static int _0x2C4CBC25(Any p0) { return invoke<int>(0x2C4CBC25, p0); } // 0x2C4CBC25
   static int _0x1C8CA53C(float p0, float p1) { return invoke<int>(0x1C8CA53C, p0, p1); } // 0x1C8CA53C
   static int _0xE8960298(float p0) { return invoke<int>(0xE8960298, p0); } // 0xE8960298
   static int _0xC78B7436() { return invoke<int>(0xC78B7436); } // 0xC78B7436
   static int _0x94DBC0C5() { return invoke<int>(0x94DBC0C5); } // 0x94DBC0C5
   static int _0xC738ED3E() { return invoke<int>(0xC738ED3E); } // 0xC738ED3E
   static int _0xD1CF9793(Any p0) { return invoke<int>(0xD1CF9793, p0); } // 0xD1CF9793
   static int _0xA8BD64D1(Any p0) { return invoke<int>(0xA8BD64D1, p0); } // 0xA8BD64D1
   static int _0x6C7A3CE6() { return invoke<int>(0x6C7A3CE6); } // 0x6C7A3CE6
   static int _0x95D0FC79(float p0) { return invoke<int>(0x95D0FC79, p0); } // 0x95D0FC79
   static int _0xC519E3F3(Any p0) { return invoke<int>(0xC519E3F3, p0); } // 0xC519E3F3
   static void ADD_AI_MOVE_RESTRICTION_STAY_OUTSIDE_OF_VOLUME_SET(Any p0, Any p1) { invoke<Void>(0xEBE88626, p0, p1); } // 0xEBE88626
   static void REMOVE_AI_MOVE_RESTRICTION_STAY_OUTSIDE_OF_VOLUME_SET(Any p0, Any p1) { invoke<Void>(0x1AED34CA, p0, p1); } // 0x1AED34CA
   static void ADD_AMBIENT_MOVE_RESTRICTION_STAY_OUTSIDE_OF_VOLUME(Any p0) { invoke<Void>(0xCF50D509, p0); } // 0xCF50D509
   static void ADD_AMBIENT_SPAWN_RESTRICTION_STAY_OUTSIDE_OF_VOLUME(Any p0) { invoke<Void>(0xD1C09A22, p0); } // 0xD1C09A22
   static void REMOVE_AMBIENT_MOVE_RESTRICTION_STAY_OUTSIDE_OF_VOLUME(Any p0) { invoke<Void>(0x515AC319, p0); } // 0x515AC319
   static void REMOVE_AMBIENT_SPAWN_RESTRICTION_STAY_OUTSIDE_OF_VOLUME(Any p0) { invoke<Void>(0xD65BAA71, p0); } // 0xD65BAA71
   static int _0x21C59F4C(Any p0) { return invoke<int>(0x21C59F4C, p0); } // 0x21C59F4C
   static int DOES_AMBIENT_SPAWN_RESTRICTION_VOLUME_EXIST(Any p0) { return invoke<int>(0x02E15363, p0); } // 0x02E15363
   static void RELEASE_ACTOR_AS_AMBIENT(Any p0) { invoke<Void>(0xC8AD4A8C, p0); } // 0xC8AD4A8C
   static int WOULD_ACTOR_BE_VISIBLE(Any p0, Any p1, Any p2) { return invoke<int>(0xD8BE8E0C, p0, p1, p2); } // 0xD8BE8E0C
   static int _0x515E17DC(Any p0) { return invoke<int>(0x515E17DC, p0); }  // 0x515E17DC
   static int _0x8ED2B0BC(Any p0, Any p1, float p2, float p3, float p4) { return invoke<int>(0x8ED2B0BC, p0, p1, p2, p3, p4); }  // 0x8ED2B0BC
   static int _0x08FD1D81(Any p0) { return invoke<int>(0x08FD1D81, p0); } // 0x08FD1D81
   static int _0x257C73C5(Any p0) { return invoke<int>(0x257C73C5, p0); } // 0x257C73C5
   static void SET_ACTOR_OBEY_AMBIENT_MOVE_RESTRICTIONS(Any p0, Any p1) { invoke<Void>(0xED3071A5, p0, p1); } // 0xED3071A5
   static int _SET_ACTOR_OBEY_AMBIENT_MOVE_RESTRICTIONS_2(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13, Any p14, Any p15, Any p16, Any p17) { return invoke<int>(0xFF642652, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17); } // 0xFF642652
   static float* _0x851F88F6(float p0) { return invoke<float*>(0x851F88F6, p0); } // 0x851F88F6
}

namespace AMBIENT2
{
   static void _0xA8226DFF() { invoke<Void>(0xA8226DFF); } // 0xA8226DFF
   static void _0x831FC466() { invoke<Void>(0x831FC466); } // 0x831FC466
   static int _0xCC9E6F4C(float x, float y, float z) { return invoke<int>(0xCC9E6F4C, x, y, z); } // 0xCC9E6F4C
   static int _0x7B07D449() { return invoke<int>(0x7B07D449); } // 0x7B07D449
   static int _0x205E891C(float x, float y, float z) { return invoke<int>(0x205E891C, x, y, z); }// 0x205E891C
   static void _0x8B011F5D() { invoke<Void>(0x8B011F5D); } // 0x8B011F5D
   static int _0x19B26C78(Any p0, Any p1) { return invoke<int>(0x19B26C78, p0, p1); } // 0x19B26C78
   static Any _0xA337135A(Any p0) { return invoke<Any>(0xA337135A, p0); } // 0xA337135A
   static Any _0x9A35520B(Any p0) { return invoke<Any>(0x9A35520B, p0); } // 0x9A35520B
   static void _0x272D756C() { invoke<Void>(0x272D756C); } // 0x272D756C
   static void AMBIENT_SET_SEARCH_CENTER_ACTOR(Any p0) { invoke<Void>(0x9A2B05F4, p0); } // 0x9A2B05F4
   static Any AMBIENT_SET_SEARCH_CENTER_PLAYER(Any p0) { return invoke<Any>(0x21E783AC, p0); } // 0x21E783AC
   static void _0x391F3607(Any p0, Any p1, float p2) { invoke<Void>(0x391F3607, p0, p1, p2); } // 0x391F3607
   static Any _0x2CCE1115(Any p0) { return invoke<Any>(0x2CCE1115, p0); } // 0x2CCE1115
   static int _0x45190938(float p0, float p1, float p2) { return invoke<int>(0x45190938, p0, p1, p2); } // 0x45190938
   static int _0x561C9A6D(Any p0) { return invoke<int>(0x561C9A6D, p0); } // 0x561C9A6D
   static int _0x912EEC43(float p0, float p1, float p2) { return invoke<int>(0x912EEC43, p0, p1, p2); } // 0x912EEC43
   static Any _0x528C7F3D(Any p0) { return invoke<Any>(0x528C7F3D, p0); } // 0x528C7F3D
   static void* _0xA89B77A7(float p0, float p1) { return invoke<Void*>(0xA89B77A7, p0, p1); } // 0xA89B77A7
   static void _0x762192EB(Any p0) { invoke<Void>(0x762192EB, p0); } // 0x762192EB
   static void _0x1900A97E(Any p0, Any p1) { invoke<Void>(0x1900A97E, p0, p1); } // 0x1900A97E
   static void _0x609514AE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x609514AE, p0, p1, p2, p3); } // 0x609514AE
   static void _0xAA99E18E(Any p0) { invoke<Void>(0xAA99E18E, p0); } // 0xAA99E18E
   static void _0x76341F1A(Any p0) { invoke<Void>(0x76341F1A, p0); } // 0x76341F1A
   static void _0x309D058C(Any p0) { invoke<Void>(0x309D058C, p0); } // 0x309D058C
   static void _0xB1609063(Any p0) { invoke<Void>(0xB1609063, p0); } // 0xB1609063
   static void _0x5A6418A2(Any p0, Any p1) { invoke<Void>(0x5A6418A2, p0, p1); } // 0x5A6418A2
   static void _0x9CD2B55F(Any p0, Any p1, Any p2) { invoke<Void>(0x9CD2B55F, p0, p1, p2); } // 0x9CD2B55F
   static const char* _0x1F7F1B79(Any p0, Any p1) { return invoke<const char*>(0x1F7F1B79, p0, p1); } // 0x1F7F1B79
   static void _0xBCD4979C(Any p0, Any p1, Any p2) { invoke<Void>(0xBCD4979C, p0, p1, p2); } // 0xBCD4979C
   static void _0x30C67D05(Any p0) { invoke<Void>(0x30C67D05, p0); } // 0x30C67D05
   static void _0x0AC99007(Any p0, Any p1) { invoke<Void>(0x0AC99007, p0, p1); } // 0x0AC99007
   static void _0xC8B149B4(Any p0) { invoke<Void>(0xC8B149B4, p0); } // 0xC8B149B4
   static void _0x54BD1C65(Any p0, Any p1) { invoke<Void>(0x54BD1C65, p0, p1); } // 0x54BD1C65
   static void _0x90008899(Any p0) { invoke<Void>(0x90008899, p0); } // 0x90008899
   static int _0x0C6EF9E1(Any p0, Any p1) { return invoke<int>(0x0C6EF9E1, p0, p1); } // 0x0C6EF9E1
}

namespace ANIM
{
   static int GET_ACTOR_ANIM_CURRENT_TIME(Any p0, Any p1) { return invoke<int>(0x8609F5E1, p0, p1); } // 0x8609F5E1
   static int SET_ACTOR_ANIM_CURRENT_TIME(Any p0, Any p1) { return invoke<int>(0x8626C1A0, p0, p1); } // 0x8626C1A0
   static BOOL IS_ACTOR_ANIM_PLAYING(Any p0, Any p1) { return invoke<BOOL>(0x1ADE21EB, p0, p1); } // 0x1ADE21EB
   static BOOL ACTOR_HAS_ANIM_LOADED(Any p0, Any p1) { return invoke<BOOL>(0x6B54BABD, p0, p1); }// 0x6B54BABD
   static int ACTOR_HAS_ANIM_SET(Any p0, Any p1) { return invoke<int>(0x31F5F57D, p0, p1); } // 0x31F5F57D
   static int _SET_ANIMATION_RATE_OVERRIDE_SCALE(Any p0) { return invoke<int>(0x3E30A514, p0); } // 0x3E30A514
   static int SET_PANIM_PARAMS(Any p0, Any p1, Any p2) { return invoke<int>(0x5941295A, p0, p1, p2); } // 0x5941295A
   static Any SET_PANIM_PHASE(Any p0, Any p1) { return invoke<Any>(0x94431F5A, p0, p1); } // 0x94431F5A
   static void SET_ACTOR_ANIM_PHASE_LOCK(Any p0, Any p1) { invoke<Void>(0xB03616C2, p0, p1); } // 0xB03616C2
   static void RELEASE_ACTOR_ANIM_PHASE_LOCK(Any p0) { invoke<Void>(0xAEBAE989, p0); } // 0xAEBAE989
   static BOOL IS_ACTOR_ANIM_PHASE_LOCKED(Any p0) { return invoke<BOOL>(0xE0AC4B86, p0); } // 0xE0AC4B86
   static void SET_ACTOR_CUTSCENE_MODE(Any p0, Any p1) { invoke<Void>(0x76ECD5F1, p0, p1); } // 0x76ECD5F1
   static void REQUEST_ANIM_SET(Any p0, Any p1) { invoke<Void>(0x2988B3FC, p0, p1); } // 0x2988B3FC
   static BOOL HAS_ANIM_SET_LOADED(Any p0) { return invoke<BOOL>(0x4FFF397D, p0); } // 0x4FFF397D
   static int REMOVE_ANIM_SET(Any p0) { return invoke<int>(0xD04A817A, p0); } // 0xD04A817A
   static Any SET_ANIM_SET_FOR_ACTOR(Any p0, Any p1, Any p2) { return invoke<Any>(0x39C1E1C0, p0, p1, p2); } // 0x39C1E1C0
   static void RESET_ANIM_SET_FOR_ACTOR(Any p0, Any p1) { invoke<Void>(0x7A6C5C2F, p0, p1); } // 0x7A6C5C2F
   static int _0xB1B643E0() { return invoke<int>(0xB1B643E0); } // 0xB1B643E0
   static Any REQUEST_ACTION_TREE(Any p0) { return invoke<Any>(0xB3039DB7, p0); } // 0xB3039DB7
   static Any HAS_ACTION_TREE_LOADED(Any p0) { return invoke<Any>(0xEEECD85E, p0); } // 0xEEECD85E
   static int REMOVE_ACTION_TREE(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0xBF4D0EFE, p0, p1, p2, p3, p4); } // 0xBF4D0EFE
   static Any SET_ACTION_NODE_FOR_ACTOR(Any p0, Any p1) { return invoke<Any>(0x5A795F3A, p0, p1); } // 0x5A795F3A
   static int SET_REACT_NODE_FOR_ACTOR(Any p0, Any p1) { return invoke<int>(0xF90F737E, p0, p1); } // 0xF90F737E
   static void RESET_REACT_NODE_FOR_ACTOR(Any p0) { invoke<Void>(0x7B17C5C3, p0); } // 0x7B17C5C3
   static int _RESET_ACTION_TREE_FOR_ACTOR(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x07EC142B, p0, p1, p2, p3, p4); } // 0x07EC142B
   static int SET_LINKED_ANIM_TARGET(Any p0, Any p1) { return invoke<int>(0x0A192D09, p0, p1); } // 0x0A192D09
   static int GET_LINKED_ANIM_TARGET(Any p0) { return invoke<int>(0xA4E9E7EE, p0); } // 0xA4E9E7EE
   static int CLEAR_LINKED_ANIM_TARGET(Any p0) { return invoke<int>(0xAC54E120, p0); } // 0xAC54E120
   static BOOL IS_ACTOR_PERFORMING_LINKED_ANIMATION(Any p0) { return invoke<BOOL>(0xCA9364C5, p0); } // 0xCA9364C5
   static BOOL IS_ACTION_NODE_PLAYING(Any p0, Any p1) { return invoke<BOOL>(0x7B19DEC6, p0, p1); } // 0x7B19DEC6
   static int _0x994F2BD1(Any p0, Any p1) { return invoke<int>(0x994F2BD1, p0, p1); } // 0x994F2BD1
   static Any IS_ACTOR_PLAYING_NODE_IN_TREE(Any p0, Any p1) { return invoke<Any>(0x4E0300E2, p0, p1); } // 0x4E0300E2
   static float _0x5E84F53E(Any p0) { return invoke<float>(0x5E84F53E, p0); } // 0x5E84F53E
   static int TOUGH_ARMOUR_GET_TUNING_REGENERATION_RATE(Any p0) { return invoke<int>(0x4AD89F02, p0); } // 0x4AD89F02
   static void TOUGH_ARMOUR_SET_TUNING_HIT_DEDUCTION(Any p0, Any p1, Any p2) { invoke<Void>(0x11542587, p0, p1, p2); } // 0x11542587
   static void TOUGH_ARMOUR_SET_TUNING_PAD_ARMOUR(Any p0, Any p1) { invoke<Void>(0xDCB9C943, p0, p1); } // 0xDCB9C943
   static void TOUGH_ARMOUR_SET_TUNING_REGENERATION_RATE(Any p0, Any p1) { invoke<Void>(0xB3F5EE8C, p0, p1); } // 0xB3F5EE8C
   static void _0xBEF6031B(Any p0, float p1) { invoke<Void>(0xBEF6031B, p0, p1); } // 0xBEF6031B
   static int SET_ACTOR_TO_SEAT(int* p0, Any p1, int* p2) { return invoke<int>(0xF349D0B6, p0, p1, p2); } // 0xF349D0B6
}

namespace ANIMAL
{
   static void ANIMAL_SPECIES_FLOCK_AND_TUNING_CLEAR_ALL() { invoke<Void>(0x5EFB415E); } // 0x5EFB415E
   static void ANIMAL_SPECIES_NEEDS_DOMESTICATION_LEVELS(Any p0) { invoke<Void>(0x1FD8BA91, p0); } // 0x1FD8BA91
   static void ANIMAL_SPECIES_SET_SPECIAL_USE_GRINGO(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x11DCCDAA, p0, p1, p2, p3, p4); } // 0x11DCCDAA
   static void ANIMAL_SPECIES_SET_UNALERTED_BEHAVIOR(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x6B6191EE, p0, p1, p2, p3); } // 0x6B6191EE
   static void ANIMAL_SPECIES_FLOCK_SET_ENABLED(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x4DF576A7, p0, p1, p2, p3); } // 0x4DF576A7
   static void ANIMAL_SPECIES_FLOCK_SET_PARAMETER(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xBF12100D, p0, p1, p2, p3, p4); } // 0xBF12100D
   static void ANIMAL_SPECIES_FLOCK_SET_BOOLEAN_PARAMETER(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x7C795382, p0, p1, p2, p3, p4); } // 0x7C795382
   static int ANIMAL_SPECIES_ADD_EXTERNAL_PATH_ATTRACTION(float p0, float p1, float p2, float p3, Any p4, Any p5, Any p6) { return invoke<int>(0x338D1CEC, p0, p1, p2, p3, p4, p5, p6); } // 0x338D1CEC
   static int ANIMAL_SPECIES_REMOVE_EXTERNAL_PATH_ATTRACTION(Any p0, Any p1, Any p2) { return invoke<int>(0xF2110753, p0, p1, p2); } // 0xF2110753
   static void ANIMAL_SPECIES_ADD_EXTERNAL_RANDOM_NOISE(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x784C514C, p0, p1, p2, p3, p4); } // 0x784C514C
   static void ANIMAL_SPECIES_ADD_EXTERNAL_REPULSION(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x4217D912, p0, p1, p2, p3, p4); } // 0x4217D912
   static void ANIMAL_SPECIES_ADD_EXTERNAL_INFLUENCE_FLOCK_REASONER(Any p0, Any p1) { invoke<Void>(0x9D8C2744, p0, p1); } // 0x9D8C2744
   static float ANIMAL_SPECIES_TUNING_GET_ATTRIB_FLOAT(Any p0, Any p1, Any p2) { return invoke<float>(0x8020C45E, p0, p1, p2); } // 0x8020C45E
   static void ANIMAL_SPECIES_TUNING_SET_ATTRIB_BOOL(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x651ACCB1, p0, p1, p2, p3); } // 0x651ACCB1
   static void ANIMAL_SPECIES_TUNING_SET_ATTRIB_FLOAT(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x20AD711E, p0, p1, p2, p3); } // 0x20AD711E
   static void ANIMAL_SPECIES_TUNING_MOVE_SET_ATTRIB(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x10CC05F1, p0, p1, p2, p3, p4); } // 0x10CC05F1
   static void ANIMAL_SPECIES_TUNING_SET_ATTACHMENT_WITH_OFFSET(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0xA6A4651B, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xA6A4651B
   static void ANIMAL_SPECIES_TUNING_SET_ATTACHMENT_WITH_CHILDBONE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x168AAB9B, p0, p1, p2, p3); } // 0x168AAB9B
   static void ANIMAL_SPECIES_TUNING_SET_HUNTING_PREY_PROP(Any p0, Any p1) { invoke<Void>(0xD05DDBB6, p0, p1); } // 0xD05DDBB6
   static void ANIMAL_SPECIES_TUNING_SET_ATTRIB_FLOAT_FROM_TIME(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x96B26945, p0, p1, p2, p3); } // 0x96B26945
   static void ANIMAL_SPECIES_INIT_BEGIN(Any p0) { invoke<Void>(0xE228CC1A, p0); } // 0xE228CC1A
   static void ANIMAL_SPECIES_INIT_REGISTER(Any p0, Any p1) { invoke<Void>(0xED6240F0, p0, p1); } // 0xED6240F0
   static void ANIMAL_SPECIES_INIT_END() { invoke<Void>(0x00760C27); } // 0x00760C27
   static void ANIMAL_SPECIES_GRINGO_CLEAR_ALL() { invoke<Void>(0xD4DDC119); } // 0xD4DDC119
   static int _ANIMAL_SPECIES_GRINGO_CLEAR_ALL() { return invoke<int>(0xBFB65BE8); } // 0xBFB65BE8
   static void ANIMAL_SPECIES_REL_CLEAR_ALL() { invoke<Void>(0x98073A48); } // 0x98073A48
   static void ANIMAL_SPECIES_REL_SET_ATTACK_GRAB_ENABLED(Any p0, Any p1, Any p2) { invoke<Void>(0x1E02527F, p0, p1, p2); } // 0x1E02527F
   static void ANIMAL_SPECIES_REL_SET_PREDATOR_AND_PREY(Any p0, Any p1) { invoke<Void>(0x84B474ED, p0, p1); } // 0x84B474ED
   static void ANIMAL_SPECIES_REL_SET_THREAT(Any p0, Any p1, Any p2) { invoke<Void>(0x9D5C43C9, p0, p1, p2); } // 0x9D5C43C9
   static void ANIMAL_SPECIES_REL_SET_AVOID(Any p0, Any p1, Any p2) { invoke<Void>(0xBF8B1BD7, p0, p1, p2); } // 0xBF8B1BD7
   static void ANIMAL_SPECIES_REL_SET_PLAY_HUNT(Any p0, Any p1, Any p2) { invoke<Void>(0x3F747178, p0, p1, p2); } // 0x3F747178
   static void ANIMAL_SPECIES_REL_SET_PLAY_CHASE(Any p0, Any p1, Any p2) { invoke<Void>(0x586904BD, p0, p1, p2); } // 0x586904BD
   static void ANIMAL_SPECIES_REL_SET_PLAY_BEG(Any p0, Any p1, Any p2) { invoke<Void>(0x70C48A1C, p0, p1, p2); } // 0x70C48A1C
   static void ANIMAL_SPECIES_REL_SET_PLAY_GROWL(Any p0, Any p1, Any p2) { invoke<Void>(0x70DE500E, p0, p1, p2); } // 0x70DE500E
   static void ANIMAL_SPECIES_REL_SET_PLAY_SNIFF(Any p0, Any p1, Any p2) { invoke<Void>(0x6606A669, p0, p1, p2); } // 0x6606A669
   static int ANIMAL_SPECIES_REL_GET_CAN_ATTACK(Any p0, Any p1) { return invoke<int>(0x3C5700DC, p0, p1); } // 0x3C5700DC
   static void ANIMAL_SPECIES_REL_SET_CAN_ATTACK(Any p0, Any p1, Any p2) { invoke<Void>(0xC8B4CD3F, p0, p1, p2); } // 0xC8B4CD3F
   static void ANIMAL_SPECIES_REL_SET_CAN_WARN(Any p0, Any p1, Any p2) { invoke<Void>(0x0482DD4E, p0, p1, p2); } // 0x0482DD4E
   static void ANIMAL_SPECIES_REL_SET_EAT_GRINGO(Any p0, Any p1, Any p2) { invoke<Void>(0xB5A63B67, p0, p1, p2); } // 0xB5A63B67
   static int ANIMAL_ACTOR_GET_DOMESTICATION(Any p0) { return invoke<int>(0xCE23118D, p0); } // 0xCE23118D
   static void ANIMAL_ACTOR_SET_DOMESTICATION(Any p0, Any p1) { invoke<Void>(0x58C36502, p0, p1); } // 0x58C36502
   static int ANIMAL_ACTOR_GET_SPECIES(Any p0) { return invoke<int>(0x7D0E25DF, p0); } // 0x7D0E25DF
   static void ANIMAL_TUNING_SET_ATTRIB_BOOL(Any p0, Any p1, Any p2) { invoke<Void>(0x11150810, p0, p1, p2); } // 0x11150810
   static void ANIMAL_TUNING_SET_ATTRIB_FLOAT(Any p0, Any p1, Any p2) { invoke<Void>(0xE36EA080, p0, p1, p2); } // 0xE36EA080
   static void ANIMAL_ACTOR_SET_DOCILE(Actor actor, BOOL p1) { invoke<Void>(0xABFCFF01, actor, p1); } // 0xABFCFF01
   static BOOL ANIMAL_ACTOR_GET_DOCILE(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<BOOL>(0xAAA8AF88, p0, p1, p2, p3, p4); } // 0xAAA8AF88
   static int _0x57DF8CD0(Any p0, Any p1) { return invoke<int>(0x57DF8CD0, p0, p1); } // 0x57DF8CD0
}

namespace ANIMATOR
{
   static BOOL IS_OBJECT_ANIMATOR_VALID(Any p0) { return invoke<BOOL>(0x19BD222F, p0); } // 0x19BD222F
   static int CREATE_OBJECT_ANIMATOR(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x856D5842, p0, p1, p3, p4); } // 0x856D5842
   static int CREATE_OBJECT_ANIMATOR_ON_OBJECT(int* p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x0D0A66B6, p0, p1, p2, p3, p4); } // 0x0D0A66B6
   static BOOL IS_OBJECT_ANIMATOR_READY(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13, Any p14, Any p15, Any p16) { return invoke<BOOL>(0x554CF528, p0, p1, p2, p3, p4, p5, p6, p7, p8, p8, p10, p11, p12, p13, p14, p14, p15, p16); } // 0x554CF528
   static int GET_OBJECT_ANIMATOR_ON_OBJECT(int* p0, Any p1) { return invoke<int>(0x5908F7FE, p0, p1); } // 0x5908F7FE
   static int SET_OBJECT_ANIMATOR_NODE(Any p0, Any p1) { return invoke<int>(0xB9D7B63B, p0, p1); } // 0xB9D7B63B
   static int SET_OBJECT_ANIMATOR_PHASE(Any p0, Any p1) { return invoke<int>(0xC0128653, p0, p1); }// 0xC0128653
   static int SET_OBJECT_ANIMATOR_RATE(Any p0, Any p1) { return invoke<int>(0x0B4D9AFA, p0, p1); } // 0x0B4D9AFA
   static float GET_OBJECT_ANIMATOR_PHASE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<float>(0xC5205015, p0, p1, p2, p3, p4, p5, p6); } // 0xC5205015
   static int _SET_BONE_RANGE_ARRAY(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x188B6431, p0, p1, p2, p3); } // 0x188B6431
   static int _0xB57D4110(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<int>(0xB57D4110, p0, p1, p2, p3, p4, p5, p6); } // 0xB57D4110
   static BOOL _IS_OBJECT_ANIMATOR_ANIM_PLAYING(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13, Any p14, Any p15, Any p16) { return invoke<BOOL>(0x46A69DAF, p0, p1, p2, p3, p4, p5, p6, p7, p8, p8, p10, p11, p12, p13, p14, p14, p15, p16); } // 0x46A69DAF
   static int DESTROY_OBJECT_ANIMATOR(Any p0) { return invoke<int>(0x1E5A227A, p0); } // 0x1E5A227A
   static Any GET_OBJECT_FROM_ANIMATOR(Any p0, Any p1) { return invoke<Any>(0x4F10FD5B, p0, p1); } // 0x4F10FD5B
   static Any LINK_OBJECT_ANIMATOR_TO_ACTOR(Any p0, Any p1, Any p2) { return invoke<Any>(0xBEDB066C, p0, p1, p2); } // 0xBEDB066C
}

namespace AUDIO
{
   static Any NEW_SCRIPTED_CONVERSATION() { return invoke<Any>(0x1CEA7FCE); } // 0x1CEA7FCE
   static void ADD_LINE_TO_CONVERSATION(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x96CD0513, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x96CD0513
   static void ADD_NEW_CONVERSATION_SPEAKER(Any p0, Any p1, Any p2) { invoke<Void>(0xF1C40BCA, p0, p1, p2); } // 0xF1C40BCA
   static void ADD_NEW_FRONTEND_CONVERSATION_SPEAKER(Any p0, Any p1) { invoke<Void>(0x4FAD0D8F, p0, p1); } // 0x4FAD0D8F
   static void START_SCRIPT_CONVERSATION(Any p0, Any p1) { invoke<Void>(0xE5DE7D9D, p0, p1); } // 0xE5DE7D9D
   static BOOL IS_SCRIPTED_CONVERSATION_ONGOING() { return invoke<BOOL>(0xCB8FD96F); } // 0xCB8FD96F
   static int PAUSE_SCRIPTED_CONVERSATION(Any p0, Any p1, Any p2) { return invoke<int>(0xE2C9C6F8, p0, p1, p2); } // 0xE2C9C6F8
   static int RESTART_SCRIPTED_CONVERSATION() { return invoke<int>(0x6CB24B56); } // 0x6CB24B56
   static int ABORT_SCRIPTED_CONVERSATION(Any p0) { return invoke<int>(0xC842F0C9, p0); } // 0xC842F0C9
   static void _0x1CFC44F9(float p0) { invoke<Void>(0x1CFC44F9, p0); } // 0x1CFC44F9
   static void _0xC1C29ABC() { invoke<Void>(0xC1C29ABC); } // 0xC1C29ABC
   static int _0x713519AB() { return invoke<int>(0x713519AB); } // 0x713519AB
   static void UNREGISTER_SCRIPT_WITH_AUDIO() { invoke<Void>(0x66728EFE); } // 0x66728EFE
   static int REQUEST_MISSION_AUDIO_BANK(const char* p0) { return invoke<int>(0x916E37CA, p0); } // 0x916E37CA
   static void MISSION_AUDIO_BANK_NO_LONGER_NEEDED() { invoke<Void>(0x4E92CC7A); } // 0x4E92CC7A
   static int AMBIENT_AUDIO_BANK_NO_LONGER_NEEDED() { return invoke<int>(0x6DCC98E9); } // 0x6DCC98E9
   static Any GET_SOUND_ID(Any p0) { return invoke<Any>(0x6AE0AD56, p0); } // 0x6AE0AD56
   static void RELEASE_SOUND_ID(Any p0) { invoke<Void>(0x9C080899, p0); } // 0x9C080899
   static BOOL IS_SOUND_ID_VALID(Any p0) { return invoke<BOOL>(0xE1D265FA, p0); } // 0xE1D265FA
   static void PLAY_SOUND(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xB6E1917F, p0, p1, p2, p3); } // 0xB6E1917F
   static int _0x09DA2503(Any p0, Any p1) { return invoke<int>(0x09DA2503, p0, p1); } // 0x09DA2503
   static int _0x66763C4A(Any p0, Any p1, Any p2) { return invoke<int>(0x66763C4A, p0, p1, p2); } // 0x66763C4A
   static void PLAY_SOUND_FRONTEND(const char* audioName) { invoke<Void>(0x2E458F74, audioName); } // 0x2E458F74
   static void _0x49053A94(Any p0, Any p1) { invoke<Void>(0x49053A94, p0, p1); } // 0x49053A94
   static void _0xB157BBB4(Any p0, Any p1) { invoke<Void>(0xB157BBB4, p0, p1); } // 0xB157BBB4
   static void PLAY_SOUND_FROM_POSITION(const char* audioName, float x, float y, float z) { invoke<Void>(0x05BC72D7, audioName, x, y, z); } // 0x05BC72D7
   static int _0x19E5CF85(Any p0, float p1, float p2, float p3, Any p4, Any p5, Any p6) { return invoke<int>(0x19E5CF85, p0, p1, p2, p3, p4, p5, p6); } // 0x19E5CF85
   static void _0x5B05E3E0(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x5B05E3E0, p0, p1, p2, p3, p4); } // 0x5B05E3E0
   static void _0x3375FB38(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x3375FB38, p0, p1, p2, p3, p4); } // 0x3375FB38
   static void PLAY_SOUND_FROM_ACTOR(Any p0, const char* p1, Any p2) { invoke<Void>(0x628832AD, p0, p1, p2); } // 0x628832AD
   static int _0x4634B6BE(Any p0, Any p1, Any p2) { return invoke<int>(0x4634B6BE, p0, p1, p2); } // 0x4634B6BE
   static void PLAY_SOUND_FROM_OBJECT(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x6A515A49, p0, p1, p2, p3); } // 0x6A515A49
   static Any _0xBD0E8EBA(Any p0) { return invoke<Any>(0xBD0E8EBA, p0); } // 0xBD0E8EBA
   static void STOP_SOUND(Any p0) { invoke<Void>(0xCD7F4030, p0); } // 0xCD7F4030
   static BOOL HAS_SOUND_FINISHED(Any p0) { return invoke<BOOL>(0xE85AEC2E, p0); } // 0xE85AEC2E
   static void _0x74CA8E22(Any p0) { invoke<Void>(0x74CA8E22, p0); } // 0x74CA8E22
   static void _0x66FCA3F7(Any p0) { invoke<Void>(0x66FCA3F7, p0); } // 0x66FCA3F7
   static void _0x14ED45FB() { invoke<Void>(0x14ED45FB); } // 0x14ED45FB
   static void _0x7D95325E() { invoke<Void>(0x7D95325E); } // 0x7D95325E
   static void _0x1BB84187() { invoke<Void>(0x1BB84187); } // 0x1BB84187
   static int _0x3DFD83DE(Any p0) { return invoke<int>(0x3DFD83DE, p0); } // 0x3DFD83DE
   static void _0xDD0320CB() { invoke<Void>(0xDD0320CB); } // 0xDD0320CB
   static int _0x31BAF169(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<int>(0x31BAF169, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x31BAF169
   static int _0xBA734A15(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xBA734A15, p0, p1, p2, p3); } // 0xBA734A15
   static int _0x031E983D(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0x031E983D, p0, p1, p2, p3, p4, p5); } // 0x031E983D
   static int _0x0871084C(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<int>(0x0871084C, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x0871084C
   static int _0x12D077CA(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x12D077CA, p0, p1, p2, p3); } // 0x12D077CA
   static int _0x91DE3A31(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0x91DE3A31, p0, p1, p2, p3, p4, p5); } // 0x91DE3A31
   static int _0xFDA41D54(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xFDA41D54, p0, p1, p2, p3); } // 0xFDA41D54
   static int _0x955E5EEB(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0x955E5EEB, p0, p1, p2, p3, p4, p5); } // 0x955E5EEB
   static int _0x755382BC(Any p0) { return invoke<int>(0x755382BC, p0); } // 0x755382BC
   static int SAY_SINGLE_LINE_STRING_BEAT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return invoke<int>(0x84A909EC, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x84A909EC
   static int _0x3F226995(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12) { return invoke<int>(0x3F226995, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 0x3F226995
   static void AUDIO_PLAY_VOCAL_EFFECT(Any p0, Any p1, Any p2) { invoke<Void>(0xC9D3A484, p0, p1, p2); } // 0xC9D3A484
   static int _0xE5F39107(Any p0, Any p1) { return invoke<int>(0xE5F39107, p0, p1); } // 0xE5F39107
   static void AUDIO_PLAY_PAIN(Any p0, Any p1) { invoke<Void>(0x123709E8, p0, p1); } // 0x123709E8
   static int _0xA7D08EE9(Any p0, Any p1, Any p2) { return invoke<int>(0xA7D08EE9, p0, p1, p2); } // 0xA7D08EE9
   static int _0xC0E28BF0(Any p0, Any p1) { return invoke<int>(0xC0E28BF0, p0, p1); } // 0xC0E28BF0
   static void SET_AMBIENT_VOICE_NAME(Any p0, Any p1) { invoke<Void>(0xBD2EA1A1, p0, p1); } // 0xBD2EA1A1
   static int _0x77402033(Any p0) { return invoke<int>(0x77402033, p0); } // 0x77402033
   static void CANCEL_CURRENTLY_PLAYING_AMBIENT_SPEECH(Actor actor) { invoke<Void>(0x4DBD473B, actor); } // 0x4DBD473B
   static BOOL IS_AMBIENT_SPEECH_PLAYING(Any p0) { return invoke<BOOL>(0x1972E8AA, p0); } // 0x1972E8AA
   static BOOL IS_SCRIPTED_SPEECH_PLAYING(Any p0) { return invoke<BOOL>(0x2C653904, p0); } // 0x2C653904
   static BOOL IS_ANY_SPEECH_PLAYING(Any p0) { return invoke<BOOL>(0x2B74A6D6, p0); } // 0x2B74A6D6
   static void AUDIO_STOP_PAIN(Any p0) { invoke<Void>(0x462B3A65, p0); } // 0x462B3A65
   static int _0x96161235(Any p0, Any p1, Any p2) { return invoke<int>(0x96161235, p0, p1, p2); } // 0x96161235
   static int _0x3184B507(Any p0, Any p1, Any p2) { return invoke<int>(0x3184B507, p0, p1, p2); } // 0x3184B507
   static int _0x489B3078(Any p0, Any p1, Any p2) { return invoke<int>(0x489B3078, p0, p1, p2); } // 0x489B3078
   static int _0xAA565B11(Any p0, Any p1, Any p2) { return invoke<int>(0xAA565B11, p0, p1, p2); } // 0xAA565B11
   static int _0x2CA089EC(Any p0, Any p1, Any p2) { return invoke<int>(0x2CA089EC, p0, p1, p2); } // 0x2CA089EC
   static int _0x43C5F320() { return invoke<int>(0x43C5F320); } // 0x43C5F320
   static int _0xF7B747CA() { return invoke<int>(0xF7B747CA); } // 0xF7B747CA
   static void SET_LOCAL_PLAYER_VOICE(Any p0) { invoke<Void>(0xF0D28043, p0); } // 0xF0D28043
   static void SET_LOCAL_PLAYER_PAIN_VOICE(const char* name) { invoke<Void>(0x33BD1A80, name); } // 0x33BD1A80
   static int _0x1F7F405C(Any p0) { return invoke<int>(0x1F7F405C, p0); } // 0x1F7F405C
   static int GRINGO_SET_MONEY_PRESENCE(Any p0) { return invoke<int>(0x2B1B76E8, p0); } // 0x2B1B76E8
   static int _0xE4D418D1(Any p0) { return invoke<int>(0xE4D418D1, p0); } // 0xE4D418D1
   static int _0xAF6A3160(Any p0, Any p1) { return invoke<int>(0xAF6A3160, p0, p1); } // 0xAF6A3160
   static int _0x94A24A5C(Any p0) { return invoke<int>(0x94A24A5C, p0); } // 0x94A24A5C
   static int _0xD021B37F(Any p0) { return invoke<int>(0xD021B37F, p0); } // 0xD021B37F
   static int _0xA343FDBB() { return invoke<int>(0xA343FDBB); } // 0xA343FDBB
   static int _0xA4F209D5() { return invoke<int>(0xA4F209D5); } // 0xA4F209D5
   static void ADD_COMPANION_PERMANENT() { invoke<Void>(0x45E20057); } // 0x45E20057
   static int* _0x15547025() { return invoke<int*>(0x15547025); } // 0x15547025
   static int _0xE0553D6B(int result, Any p1) { return invoke<int>(0xE0553D6B, result, p1); } // 0xE0553D6B //WantedMeter
   static int _0xD68E04BB(int result, Any p1) { return invoke<int>(0xD68E04BB, result, p1); }  // 0xD68E04BB //WantedMeter
   static int _0x638EAF70(Any p0, Any p1) { return invoke<int>(0x638EAF70, p0, p1); } // 0x638EAF70
   static int _0xEA975A79(Any p0, Any p1) { return invoke<int>(0xEA975A79, p0, p1); }  // 0xEA975A79
   static int _0x6BB42C21(int result) { return invoke<int>(0x6BB42C21, result); } // 0x6BB42C21 //WantedMeter
   static int _0x0E634931(int result) { return invoke<int>(0x0E634931, result); } // 0x0E634931
   static int _0x567712E5(int result) { return invoke<int>(0x567712E5, result); } // 0x567712E5
   static int _0xB888B369(int result) { return invoke<int>(0xB888B369, result); } // 0xB888B369
   static int _0x306D9FEE(int result) { return invoke<int>(0x306D9FEE, result); } // 0x306D9FEE
   static int _0xC3614E0A(int result) { return invoke<int>(0xC3614E0A, result); } // 0xC3614E0A
   static int _0xF962F2B8(int result) { return invoke<int>(0xF962F2B8, result); } // 0xF962F2B8
   static int _0x22D0DF9B(int result) { return invoke<int>(0x22D0DF9B, result); } // 0x22D0DF9B
   static int _0xA234C5D0(int result) { return invoke<int>(0xA234C5D0, result); } // 0xA234C5D0
   static int _0x733BA9F5(int result) { return invoke<int>(0x733BA9F5, result); } // 0x733BA9F5
   static int _0x79351E54(int result) { return invoke<int>(0x79351E54, result); } // 0x79351E54
   static int _0xCCBE7F0F(int result) { return invoke<int>(0xCCBE7F0F, result); } // 0xCCBE7F0F
   static int _0x5FCF3B85(int result) { return invoke<int>(0x5FCF3B85, result); } // 0x5FCF3B85
   static int _0x9D886C2F(Any p0, Any p1) { return invoke<int>(0x9D886C2F, p0, p1); } // 0x9D886C2F
   static int _0x39F5EF0F(Any p0, Any p1) { return invoke<int>(0x39F5EF0F, p0, p1); } // 0x39F5EF0F
   static int _0xD6CC6907(Any p0, Any p1) { return invoke<int>(0xD6CC6907, p0, p1); } // 0xD6CC6907
   static int _0x714D5D09(Any p0, Any p1) { return invoke<int>(0x714D5D09, p0, p1); } // 0x714D5D09
   static int _0xBF959948(Any p0) { return invoke<int>(0xBF959948, p0); } // 0xBF959948
   static int _0x3C163FDD(Any p0) { return invoke<int>(0x3C163FDD, p0); } // 0x3C163FDD
   static Any _0xDC330FB9(Any p0) { return invoke<Any>(0xDC330FB9, p0); } // 0xDC330FB9
   static int _0x39EF8DA7() { return invoke<int>(0x39EF8DA7); } // 0x39EF8DA7
   static int _0x0079FD0F() { return invoke<int>(0x0079FD0F); } // 0x0079FD0F
   static int _0x67770F4B(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x67770F4B, p0, p1, p2, p3); } // 0x67770F4B
   static int _0x8A6D03BE(Any p0) { return invoke<int>(0x8A6D03BE, p0); } // 0x8A6D03BE
   static Any _0x90DD37E7(Any p0, Any p1, Any p2) { return invoke<Any>(0x90DD37E7, p0, p1, p2); } // 0x90DD37E7
   static void STOP_PED_SPEAKING(Any p0, Any p1) { invoke<Void>(0xFF92B49D, p0, p1); } // 0xFF92B49D
   static void AUDIO_MISSION_INIT() { invoke<Void>(0xEB8A51C2); } // 0xEB8A51C2
   static void AUDIO_MISSION_RELEASE() { invoke<Void>(0xFF92B49D); } // 0xD1FD31DE
   static void _0xEB866555() { invoke<Void>(0xEB866555); } // 0xEB866555
   static void AUDIO_MUSIC_FORCE_TRACK(const char* p0, const char* p1, Any p2, Any p3, Any p4, float p5, Any p6) { invoke<Void>(0xA2A356A7, p0, p1, p2, p3, p4, p5, p6); } // 0xA2A356A7
   static void AUDIO_MUSIC_FORCE_TRACK_HASH(int hash, const char* p1, float p2, float p3, Any p4, Any p5, Any p6) { invoke<Void>(0x6CEFA97A, hash, p1, p2, p3, p4, p5, p6); } // 0x6CEFA97A
   static int _AUDIO_MUSIC_PLAY_TRACK_2(Any p0, const char* p1, float p2, float p3, Any p4, Any p5, Any p6) { return invoke<int>(0x2ACEE2ED, p0, p1, p2, p3, p4, p5, p6); } // 0x2ACEE2ED
   static int _AUDIO_MUSIC_PLAY_TRACK(Any p0, const char* p1, float p2, float p3, Any p4, Any p5, Any p6) { return invoke<int>(0x85A35B18, p0, p1, p2, p3, p4, p5, p6); } // 0x85A35B18
   static void AUDIO_MUSIC_SET_MOOD(const char* p0, Any p1, Any p2, Any p3) { invoke<Void>(0x633B8905, p0, p1, p2, p3); } // 0x633B8905
   static void AUDIO_MUSIC_ONE_SHOT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x714DA5BB, p0, p1, p2, p3, p4, p5); } // 0x714DA5BB
   static int AUDIO_MUSIC_PLAY_PREPARED() { return invoke<int>(0x7CC2738F); } // 0x7CC2738F
   static int _0x704DBAC9(Any p0) { return invoke<int>(0x704DBAC9, p0); } // 0x704DBAC9
   static int AUDIO_MUSIC_IS_PREPARED() { return invoke<int>(0xBF316157); } // 0xBF316157
   static void AUDIO_MUSIC_SET_STATE(Any p0) { invoke<Void>(0x789C753C, p0); } // 0x789C753C
   static void AUDIO_MUSIC_RELEASE_CONTROL(Any p0, Any p1) { invoke<Void>(0xA3A2984E, p0, p1); } // 0xA3A2984E
   static void AUDIO_MUSIC_SUSPEND(Any p0) { invoke<Void>(0x56E3D235, p0); } // 0x56E3D235
   static void AUDIO_MUSIC_RESUME() { invoke<Void>(0x5F48A85B); } // 0x5F48A85B
   static BOOL AUDIO_IS_MUSIC_PLAYING() { return invoke<BOOL>(0x84435231); } // 0x84435231
   static int AUDIO_IS_SCRIPTED_MUSIC_PLAYING() { return invoke<int>(0x86E995D1); } // 0x86E995D1
   static BOOL AUDIO_IS_FRONTEND_MUSIC_PLAYING() { return invoke<BOOL>(0x9EC502D6); } // 0x9EC502D6
   static void AUDIO_MUSIC_SET_SUSPENSE_ALLOWED() { invoke<BOOL>(0xE0DE16BD); } // 0xE0DE16BD
   static void AUDIO_MUSIC_PLAY_UNSCRIPTED_NOW() { invoke<Void>(0xE2A37056); } // 0xE2A37056
   static void _0x72168160() { invoke<Void>(0x72168160); } // 0x72168160
   static int* _0xB3C3FF5E() { return invoke<int*>(0xB3C3FF5E); } // 0xB3C3FF5E
   static int* _0xEA2B35DB() { return invoke<int*>(0xEA2B35DB); } // 0xEA2B35DB
   static int _0x0CCE435E(float p0, float p1, float p2) { return invoke<int>(0x0CCE435E, p0, p1, p2); } // 0x0CCE435E
   static int _0x7784BB85() { return invoke<int>(0x7784BB85); } // 0x7784BB85
   static int _0x24AE7AFB() { return invoke<int>(0x24AE7AFB); }  // 0x24AE7AFB
   static int _0xDE7C65CE() { return invoke<int>(0xDE7C65CE); } // 0xDE7C65CE
   static int _0x338DF299() { return invoke<int>(0x338DF299); } // 0x338DF299
   static int _0x2D40E85C(Any p0, Any p1, Any p2) { return invoke<int>(0x2D40E85C, p0, p1, p2); } // 0x2D40E85C
   static int _0x900C489A() { return invoke<int>(0x900C489A); } // 0x900C489A
   static int _0xE8FFE727() { return invoke<int>(0xE8FFE727); } // 0xE8FFE727
   static int _0xB73AC04A() { return invoke<int>(0xB73AC04A); } // 0xB73AC04A
   static int _0xBFCF32D9() { return invoke<int>(0xBFCF32D9); } // 0xBFCF32D9
   static int _0x37FD00EA() { return invoke<int>(0x37FD00EA); } // 0x37FD00EA
   static BOOL _IS_AUDIO_BANK_LOADING(const char* p0, const char* p1) { return invoke<BOOL>(0x98CD7340, p0, p1); } // 0x98CD7340
   static void LOAD_AUDIO_BANK(const char* p0, const char* p1) { invoke<Void>(0x08F4B5B8, p0, p1); } // 0x08F4B5B8
   static int _0x176E921C() { return invoke<int>(0x176E921C); } // 0x176E921C
   static int _0xBAEC56D1(Any p0) { return invoke<int>(0xBAEC56D1); } // 0xBAEC56D1
}

namespace CAM
{
   static Any GET_GAME_CAMERA() { return invoke<Any>(0x6B7677BF); } // 0x6B7677BF
   static void CAMERA_RESET(Any p0) { invoke<Void>(0xCE956B28, p0); } // 0xCE956B28
   static void _0x39E59CD8() { invoke<Void>(0x39E59CD8); } // 0x39E59CD8
   static BOOL CAMERA_PROBE(Vector3* result, Vector3 source, Vector3 target, Actor owner, int flag) { return invoke<BOOL>(0x720F2CA7, result, source, target, owner, flag); } // 0x720F2CA7
   static int _0xC783B9B9() { return invoke<int>(0xC783B9B9); } // 0xC783B9B9
   static int GET_GAME_CAMERA_RESET_POSITION(Any p0, Any p1, float p2, float p3, float p4, float p5, Any p6, Any p7, Any p8, const char* p9) { return invoke<int>(0x0B071844, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x0B071844
   static int SET_CAMERA_FOLLOW_ACTOR(Any p0) { return invoke<int>(0x8EFDFE89, p0); } // 0x8EFDFE89
   static int _0x457A0510(Any p0, Any p1) { return invoke<int>(0x457A0510, p0, p1); } // 0x457A0510
   static int _0x9B083FD2() { return invoke<int>(0x9B083FD2); } // 0x9B083FD2
   static int _0x063F900A(Any p0) { return invoke<int>(0x063F900A, p0); } // 0x063F900A
   static int _0x507BBD3A(Any p0, Any p1) { return invoke<int>(0x507BBD3A, p0, p1); } // 0x507BBD3A
   static int _0xC93116B1() { return invoke<int>(0xC93116B1); } // 0xC93116B1
   static void FORCE_VEHICLE_CINEMATIC_CAMERA(Any p0) { invoke<Void>(0x09737AF7, p0); } // 0x09737AF7
   static int _0x72960AE2() { return invoke<int>(0x72960AE2); } // 0x72960AE2
   static int _0x382C47C5(Any p0) { return invoke<int>(0x382C47C5, p0); } // 0x382C47C5
   static int _0x6E303287(Any p0, Any p1) { return invoke<int>(0x6E303287, p0, p1); } // 0x6E303287
   static int _0xE13B49BD(Any p0) { return invoke<int>(0xE13B49BD); } // 0xE13B49BD
   static int _0x9603D3B2(Any p0, Any p1) { return invoke<int>(0x9603D3B2, p0, p1); } // 0x9603D3B2
   static int _0x4062688A(Any p0) { return invoke<int>(0x4062688A, p0); } // 0x4062688A
   static int* _0x3AE77125(float p0, float p1, float p2, Any p3, Any p4, Any p5) { return invoke<int*>(0x3AE77125, p0, p1, p2, p3, p4, p5); } // 0x3AE77125
   static int ENABLE_GAME_CAMERA_FOCUS(float p0, float p1, float p2, float p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return invoke<int>(0x87E40FB8, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x87E40FB8
   static int DISABLE_GAME_CAMERA_FOCUS() { return invoke<int>(0x4FA19C01); } // 0x4FA19C01
   static int _0x5BD2295E() { return invoke<int>(0x5BD2295E); } // 0x5BD2295E
   static int  _0xF3623B64() { return invoke<int>(0xF3623B64); } // 0xF3623B64
   static int _0xAE168124() { return invoke<int>(0xAE168124); } // 0xAE168124
   static BOOL _0x9F1F8669(BOOL p0) { return invoke<BOOL>(0x9F1F8669, p0); } // 0x9F1F8669
}

namespace CAMERA
{
   static int _0x0B1569C5(Any p0, Any p1, Any p2) { return invoke<int>(0x0B1569C5, p0, p1, p2); } // 0x0B1569C5
   static int _0xBCC98808(Any p0) { return invoke<int>(0xBCC98808, p0); } // 0xBCC98808
   static void SET_CURRENT_CAMERA_ON_CHANNEL(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0x3EA55678, p0, p1, p3, p4, p5, p6, p7, p8, p9); } // 0x3EA55678
   static void REMOVE_CAMERA_FROM_CHANNEL(Any p0, Any p1) { invoke<Void>(0x423DB420, p0, p1); } // 0x423DB420
   static int GET_CAMERA_CHANNEL_POSITION(Any p0, Any p1) { return invoke<int>(0xE017E2F7, p0, p1); } // 0xE017E2F7
   static int GET_CAMERA_CHANNEL_DIRECTION(Any p0, Any p1) { return invoke<int>(0x6ED00237, p0, p1); } // 0x6ED00237
   static int _0x9A4CD54B(Any p0) { return invoke<int>(0x9A4CD54B, p0); } // 0x9A4CD54B
   static BOOL IS_CAMERA_ACTIVE_ON_CHANNEL(Any p0, Any p1) { return invoke<BOOL>(0x02BD5362, p0, p1); } // 0x02BD5362
   static void INIT_CAMERA_FROM_GAME_CAMERA(Any p0) { invoke<Void>(0x2615309A, p0); } // 0x2615309A
   static void INIT_CAMERA_FROM_CHANNEL(Any p0, Any p1) { invoke<Void>(0x41EA7325, p0, p1); } // 0x41EA7325
   static void SET_CAMERA_POSITION(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x0B12CD8C, p0, p1, p2, p3); } // 0x0B12CD8C
   static void GET_CAMERA_POSITION(Any p0, Any* p1, Any* p2, Any* p3) { invoke<Void>(0x4A65F0B7, p0, p1, p2, p3); } // 0x4A65F0B7
   static void SET_CAMERA_DIRECTION(Camera Cam, Vector3 Direction, BOOL p0) { invoke<Void>(0xA8642E5E, Cam, Direction, p0); } // 0xA8642E5E
   static void GET_CAMERA_DIRECTION(Any p0, Any* p1, Any* p2, Any* p3) { invoke<Void>(0xBBD1078A, p0, p1, p2, p3); } // 0xBBD1078A
   static void GET_CAMERA_UP_VECTOR(Any p0, Any p1) { invoke<Void>(0x94A10ECD, p0, p1); } // 0x94A10ECD
   static void SET_CAMERA_FOV(Any p0, Any p1) { invoke<Void>(0x57E3242D, p0, p1); } // 0x57E3242D
   static int GET_CAMERA_FOV(Any p0) { return invoke<int>(0x7B302F36, p0); } // 0x7B302F36
   static void SET_CAMERA_ASPECT_RATIO(Any p0, Any p1) { invoke<Void>(0xFAEE2667, p0, p1); } // 0xFAEE2667
   static float GET_CAMERA_ASPECT_RATIO(Any p0) { return invoke<float>(0xCE01609D, p0); } // 0xCE01609D
   static void SET_CAMERA_NEAR_CLIP_PLANE(Any p0, Any p1) { invoke<Void>(0x1D29E72A, p0, p1); } // 0x1D29E72A
   static void SET_CAMERA_FAR_CLIP_PLANE(Any p0, Any p1) { invoke<Void>(0xD85EF521, p0, p1); } // 0xD85EF521
   static void SET_CAMERA_ORIENTATION(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x486F4461, p0, p1, p2, p3, p4); } // 0x486F4461
   static void SET_CAMERA_TARGET_POSITION(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x298BCCA5, p0, p1, p2, p3, p4); } // 0x298BCCA5
   static void SET_CAMERA_TARGET_OBJECT(Any p0, Any p1, Any p2) { invoke<Void>(0xDBD1AE22, p0, p1, p2); } // 0xDBD1AE22
   static void SET_CAMERA_COLLISION_PARAMETERS(Any p0, Any p1, Any p2) { invoke<Void>(0xB8FAD252, p0, p1, p2); } // 0xB8FAD252
   static void ADD_CAMERA_COLLISION_EXCLUSION(Any p0, Any p1, Any p2) { invoke<Void>(0x5BBFA4D7, p0, p1, p2); } // 0x5BBFA4D7
   static void REMOVE_CAMERA_COLLISION_EXCLUSION(Any p0, Any p1) { invoke<Void>(0x781D5599, p0, p1); } // 0x781D5599
   static void RESET_CAMERA_TARGET(Any p0, Any p1) { invoke<Void>(0x313A4E61, p0, p1); } // 0x313A4E61
   static void SET_CAMERA_COLLISION_ENABLED(Any p0, Any p1) { invoke<Void>(0x7DA71AA7, p0, p1); } // 0x7DA71AA7
   static int SET_CAMERA_TARGETDOF_FOCAL_LENGTH(Any p0, float p1) { return invoke<int>(0x3010BBC2, p0, p1); } // 0x3010BBC2
   static void SET_CAMERA_TARGETDOF_USING_SOFT_DOF(Any p0, Any p1, Any p2) { invoke<Void>(0x7F1C5102, p0, p1, p2); } // 0x7F1C5102
   static void RESET_CAMERA_TARGETDOF(Any p0) { invoke<Void>(0x4643D2C7, p0); } // 0x4643D2C7
   static Any SET_CAMERA_LIGHTING_SCHEME(Any p0, Any p1) { return invoke<Any>(0x7C864F17, p0, p1); } // 0x7C864F17
   static int CAMERA_GET_CURRENT_TRANSITION_TYPE(Any p0) { return invoke<int>(0xE55B5ADB, p0); } // 0xE55B5ADB
   static int CAMERA_IS_VISIBLE_OBJECT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<int>(0x965A4652, p0, p1, p2, p3, p4, p5, p6); } // 0x965A4652
   static int CAMERA_IS_VISIBLE_ACTOR(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<int>(p0, p1, p2, p3, p4, p5, p6); } // 0xBB6FDF5F
   static int CAMERA_IS_VISIBLE_POINT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<int>(0xA97770FE, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xA97770FE
   static Camera CAMERA_IS_VISIBLE_VOLUME(Cam p0, Cam p1, Cam p2, Cam p3, Cam p4, Cam p5, Cam p6) { return invoke<Camera>(0xA161768C, p0, p1, p2, p3, p4, p5, p6); } // 0xA161768C
   static int _0x54A417F3(Any p0, Any p1) { return invoke<int>(0x54A417F3, p0, p1); } // 0x54A417F3
   static void INIT_CAMERASHOT_FROM_GAME_CAMERA(Any p0) { invoke<Void>(0x99314873, p0); } // 0x99314873
   static void FORCE_CAMERASHOT_UPDATE(Any p0) { invoke<Void>(0xF5CA55D4, p0); } // 0xF5CA55D4
   static void SET_CAMERASHOT_POSITION(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x0EA022F5, p0, p1, p2, p3); } // 0x0EA022F5
   static void GET_CAMERASHOT_POSITION(Any p0, Any p1) { invoke<Void>(0x4D05D470, p0, p1); } // 0x4D05D470
   static void SET_CAMERASHOT_DIRECTION(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x21B099AB, p0, p1, p2, p3, p4); } // 0x21B099AB
   static void GET_CAMERASHOT_DIRECTION(Any p0, Any p1) { invoke<Void>(0x4670416D, p0, p1); } // 0x4670416D
   static int GET_CAMERASHOT_UP_VECTOR(Any p0, Any p1) { return invoke<int>(0x83F3336B, p0, p1); } // 0x83F3336B
   static int GET_CAMERASHOT_X_VECTOR(Any p0, Any p1) { return invoke<int>(0x7597BC24, p0, p1); } // 0x7597BC24
   static void SET_CAMERASHOT_FOV(Any p0, Any p1) { invoke<Void>(0x635E5494, p0, p1); } // 0x635E5494
   static int GET_CAMERASHOT_FOV(Any p0) { return invoke<int>(0xEAD6167D, p0); } // 0xEAD6167D
   static void _SET_CAMERA_SHOT_ASPECT_RATIO(Any p0, Any p1) { invoke<Void>(0x3DEB0933, p0, p1); } // 0x3DEB0933
   static void SET_CAMERASHOT_NEAR_CLIP_PLANE(Any p0, Any p1) { invoke<Void>(0x4387CDAB, p0, p1); } // 0x4387CDAB
   static void SET_CAMERASHOT_FAR_CLIP_PLANE(Any p0, Any p1) { invoke<Void>(0x6BA86494, p0, p1); } // 0x6BA86494
   static int GET_CAMERASHOT_FAR_CLIP_PLANE(Any p0) { return invoke<int>(0xD86CB952, p0); } // 0xD86CB952
   static void SET_CAMERASHOT_ORIENTATION(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x4FD679BD, p0, p1, p2, p3, p4); } // 0x4FD679BD
   static void SET_CAMERASHOT_TARGET_POSITION(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x0D6EC5D5, p0, p1, p2, p3, p4); } // 0x0D6EC5D5
   static void SET_CAMERASHOT_TARGET_OBJECT(Any p0, Any p1, Any p2) { invoke<Void>(0x3F719473, p0, p1, p2); } // 0x3F719473
   static void SET_CAMERASHOT_TARGET_OBJECT_OFFSETS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x839E9502, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x839E9502
   static void SET_CAMERASHOT_TARGET_OBJECT_ROLL(Any p0, Any p1) { invoke<Void>(0x8014323A, p0, p1); } // 0x8014323A
   static void SET_CAMERASHOT_TARGET_OBJECT_BONE(Any p0, Any p1, Any p2) { invoke<Void>(0x4E6DDD27, p0, p1); } // 0x4E6DDD27
   static void SET_CAMERASHOT_FROM_LENS(Any p0, Any p1) { invoke<Void>(0x6F483443, p0, p1); } // 0x6F483443
   static void SET_CAMERASHOT_TARGETDOF_OBJECT(Any p0, Any p1) { invoke<Void>(0xB6BDCF62, p0, p1); } // 0xB6BDCF62
   static void SET_CAMERASHOT_TARGETDOF_TARGET_OFFSET(Any p0, Any p1) { invoke<Void>(0x087B8DCE, p0, p1); } // 0x087B8DCE
   static void SET_CAMERASHOT_TARGETDOF_FIXED_DISTANCE(Any p0, Any p1) { invoke<Void>(0xEF0AB304, p0, p1); } // 0xEF0AB304
   static void SET_CAMERASHOT_TARGETDOF_FOCAL_LENGTH(Any p0, Any p1) { invoke<Void>(0x0AD50615, p0, p1); } // 0x0AD50615
   static void SET_CAMERASHOT_TARGETDOF_CUTOFF_DISTANCE(Any p0, Any p1) { invoke<Void>(0xEB9E1CB9, p0, p1); } // 0xEB9E1CB9
   static void SET_CAMERASHOT_TARGETDOF_SMOOTHING(Any p0, Any p1) { invoke<Void>(0x74168B5F, p0, p1); } // 0x74168B5F
   static void SET_CAMERASHOT_TARGETDOF_USING_SOFT_DOF(Any p0, Any p1, Any p2) { invoke<Void>(0x0370451C, p0, p1, p2); } // 0x0370451C
   static void SET_CAMERASHOT_TARGETDOF_FILTERTYPE(Any p0, Any p1) { invoke<Void>(0x243CF01F, p0, p1); } // 0x243CF01F
   static void SET_CAMERASHOT_TARGETDOF_FSTOP(Any p0, Any p1) { invoke<Void>(0x9E618676, p0, p1); } // 0x9E618676
   static void RESET_CAMERASHOT_TARGETDOF(Any p0) { invoke<Void>(0x42327DAC, p0); } // 0x42327DAC
   static void SET_CAMERASHOT_COLLISION_PARAMETERS(Any p0, Any p1, Any p2) { invoke<Void>(0xF70817E0, p0, p1, p2); } // 0xF70817E0
   static void ADD_CAMERASHOT_COLLISION_EXCLUSION(Any p0, Any p1, Any p2) { invoke<Void>(0x58A0BFBF, p0, p1, p2); } // 0x58A0BFBF
   static void ADD_CAMERASHOT_COLLISION_BOUNDFLAG(Any p0, Any p1) { invoke<Void>(0xCD28C63F, p0, p1); } // 0xCD28C63F
   static int RESET_CAMERASHOT_TARGET(Any p0, Any p1) { return invoke<int>(0xC3DDCE4D, p0, p1); } // 0xC3DDCE4D
   static void SET_CAMERASHOT_PERSPECTIVE(Any p0, Any p1) { invoke<Void>(0xD8D27321, p0, p1); } // 0xD8D27321
   static void SET_CAMERASHOT_CONTROL_SEQUENCE_VEC3(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0x0229585E, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x0229585E
   static int ADD_CAMERA_SHOT_TRANSITION_HOLD(Any p0, Any p1, Any p2, float p3, Any p4, Any p5) { return invoke<int>(0x8F5BC02D, p0, p1, p2, p3, p4, p5); } // 0x8F5BC02D
   static int ADD_CAMERA_SHOT_TRANSITION_INDEFINITE(Any p0, Any p1, Any p2) { return invoke<int>(0xBF9B4FC6, p0, p1, p2); } // 0xBF9B4FC6
   static int ADD_CAMERA_SHOT_TRANSITION_EASE_OUT(Any p0, Any p1, Any p2, Any p3, Any p4, float p5, Any p6, Any p7, const char* p8) { return invoke<int>(0x6D72797D, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x6D72797D
   static int ADD_CAMERA_SHOT_TRANSITION_EASE_IN_OUT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0x6E10E587, p0, p1, p2, p3, p4, p5); } // 0x6E10E587
   static void SET_FIXED_TRANSITION_T(Any p0, Any p1) { invoke<Void>(0x143A617C, p0, p1); }// 0x143A617C
   static void SET_TRANSITION_COLLISION_PARAMS(Any p0, Any p1, Any p2) { invoke<Void>(0x22A746E1, p0, p1, p2); } // 0x22A746E1
   static int GET_CAMERA_SHOT_TRANSITION(Any p0) { return invoke<int>(0x7AC13DF5, p0); } // 0x7AC13DF5
   static BOOL IS_PROCESSING_CAMERA_SHOT_TRANSITION(Any p0) { return invoke<BOOL>(0xDDB64AA9, p0); } // 0xDDB64AA9
   static void END_CURRENT_CAMERA_SHOT_TRANSITION(Any p0) { invoke<Void>(0x01C1F583, p0); } // 0x01C1F583
   static void SET_CAMERASHOT_COLLISION_ENABLED(Any p0, Any p1) { invoke<Void>(0x3A07F60F, p0, p1); } // 0x3A07F60F
   static void SET_CUTSCENE_STREAMING_LOAD_SCENE(Any p0, Any p1) { invoke<Void>(0x39D1CC17, p0, p1); } // 0x39D1CC17
   static int ATTACH_CAMERASHOT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { return invoke<int>(0x41514AA0, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0x41514AA0
   static void DETACH_CAMERASHOT(Any p0) { invoke<Void>(0x059BBAA8, p0); } // 0x059BBAA8
   static int CAMERASHOT_IS_VISIBLE_ACTOR(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<int>(0xCBA91134, p0, p1, p2, p3, p4, p5, p6); } // 0xCBA91134
   static void CAMERASHOT_ADD_ARC_BEHAVIOR(Any p0, Any p1) { invoke<Void>(0xA1C665E0, p0, p1); } // 0xA1C665E0
   static void CAMERASHOT_ADD_LOOKSTICK_ROTATION_BEHAVIOR(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x59AE458A, p0, p1, p2, p3, p4, p5, p6); } // 0x59AE458A
   static int _0xDA50B18B(Any p0, Any p1) { return invoke<int>(0xDA50B18B, p0, p1); } // 0xDA50B18B
   static void UPDATE_AIMRAMP(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x86066A65, p0, p1, p2, p3, p4); } // 0x86066A65
   static int _0xA923A22D(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xA923A22D, p0, p1, p2, p3); } // 0xA923A22D
   static int GET_CAMERA_FROM_CUTSCENEOBJECT(Any p0) { return invoke<int>(0xFDBE95AE, p0); } // 0xFDBE95AE
   static void PLAY_CUTSCENEOBJECT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0xFB28AE8D, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xFB28AE8D
   static Any GET_CAMERASHOT_FROM_CUTSCENEOBJECT(Any p0, Any p1) { return invoke<Any>(0x7E9CC966, p0, p1); } // 0x7E9CC966
   static int CUTSCENEOBJECT_ADD_TRANSITION_HOLD(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xC0CD3C96, p0, p1, p2, p3); } // 0xC0CD3C96
   static int CUTSCENEOBJECT_ADD_TRANSITION_LERP(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0xFC676413, p0, p1, p2, p3, p4, p5); } // 0xFC676413
   static int CUTSCENEOBJECT_ADD_TRANSITION_EASE_IN(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0xCC61CC5F, p0, p1, p2, p3, p4, p5); } // 0xCC61CC5F
   static int CUTSCENEOBJECT_ADD_TRANSITION_EASE_OUT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0x1AD38A53, p0, p1, p2, p3, p4, p5); } // 0x1AD38A53
   static int CUTSCENEOBJECT_ADD_TRANSITION_EASE_IN_OUT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0xDB07C72B, p0, p1, p2, p3, p4, p5); } // 0xDB07C72B
   static int CUTSCENEOBJECT_ADD_TRANSITION_INDEFINITE(Any p0, Any p1, Any p2) { return invoke<int>(0x94B288F9, p0, p1, p2); } // 0x94B288F9
   static int CUTSCENEOBJECT_ADD_TRANSITION_DECORATOR(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<int>(0xA9AB9A06, p0, p1, p2, p3, p4, p5, p6); } // 0xA9AB9A06
   static int CUTSCENEOBJECT_ADD_TRANSITION_FIXED(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x7A48EDDF, p0, p1, p2, p3, p4); }   // 0x7A48EDDF
   static int CUTSCENEOBJECT_GET_CURRENT_TRANSITION_TYPE(Any p0) { return invoke<int>(0x0A776763, p0); } // 0x0A776763
   static void END_CURRENT_TRANSITION_FROM_CUTSCENEOBJECT(Any p0) { invoke<Void>(0xBE3F0168, p0); } // 0xBE3F0168
   static void SET_CUTSCENEOBJECT_PAUSED(Any p0, Any p1) { invoke<Void>(0x18643DC2, p0, p1); } // 0x18643DC2
   static BOOL IS_CUTSCENEOBJECT_PAUSED(Any p0) { return invoke<BOOL>(0xD5C66699, p0); } // 0xD5C66699
   static int CHECK_CUTSCENE_COLLISIONS(Any p0) { return invoke<int>(0xE147BA8E, p0); } // 0xE147BA8E
   static int GET_CUTSCENEOBJECT_SEQUENCE(Any p0) { return invoke<int>(0x3D26D852, p0); } // 0x3D26D852
   static void _CUTSCENE_SET_RECENTER_GAMECAM(Any p0, Any p1) { invoke<Void>(0xDCD3A7DE, p0, p1); } // 0xDCD3A7DE
   static int SET_CUTSCENEINPUTS_TARGET_GUID(Any p0, Any p1, Any p2) { return invoke<int>(0xF74B5ADE, p0, p1, p2); } // 0xF74B5ADE
   static void ADD_CAMERATRANSITION_EVENT_HUDFADEIN(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x25A58402, p0, p1, p2, p3); } // 0x25A58402
   static void ADD_CAMERATRANSITION_EVENT_HUDFADEOUT(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x269F5C75, p0, p1, p2, p3); } // 0x269F5C75
   static int ADD_CAMERATRANSITION_EVENT_GAMECAMERARESET(Any p0, float p1, float p2, Any p3, Any p4) { return invoke<int>(0x699332B0, p0, p1, p2, p3, p4); } // 0x699332B0
   static void ADD_CAMERATRANSITION_EVENT_GAMECAMERARESETTILT(Any p0, Any p1) { invoke<Void>(0x3A8487A6, p0, p1); } // 0x3A8487A6
   static void ADD_CAMERATRANSITION_EVENT_CUTGAMECAMERABEHINDPLAYER(Any p0, Any p1, Any p2) { invoke<Void>(0x8D7070F3, p0, p1, p2); } // 0x8D7070F3
   static int _0xCDA6BB6C() { return invoke<int>(0xCDA6BB6C); } // 0xCDA6BB6C
   static void _0xE7A1C191() { invoke<Void>(0xE7A1C191); } // 0xE7A1C191
   static int _0x93050734() { return invoke<int>(0x93050734); } // 0x93050734
   static int _0xFF1F1730() { return invoke<int>(0xFF1F1730); }// 0xFF1F1730
   static int* _0x74EE96B8() { return invoke<int*>(0x74EE96B8); } // 0x74EE96B8
   static int _0xD8218A5B() { return invoke<int>(0xD8218A5B); } // 0xD8218A5B
   static int _0x6AD6A400(int* p0, Any p1, Any p2, float p3, float p4, float p5, float p6, float p7) { return invoke<int>(0x6AD6A400, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x6AD6A400
   static int _0x76876FEA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<int>(0x76876FEA, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x76876FEA
   static int _0x7A6146DB(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0x7A6146DB, p0, p1, p2, p3, p4, p5); } // 0x7A6146DB
   static BOOL IS_CAMERA_FOCUS_ACTIVE(Any p0) { return invoke<BOOL>(0xCA8CC5CE, p0); } // 0xCA8CC5CE
   static void SET_CAMERA_FOCUS_ENABLED(Any p0, Any p1) { invoke<Void>(0x78D29E49, p0, p1); } // 0x78D29E49
   static BOOL IS_CAMERA_FOCUS_ENABLED(Any p0) { return invoke<BOOL>(0x80D63DAC, p0); } // 0x80D63DAC
   static void SET_CAMERA_FOCUS_PROMPT_ENABLED(Any p0, Any p1) { invoke<Void>(0x2148298D, p0, p1); } // 0x2148298D
   static BOOL IS_CAMERA_FOCUS_PROMPT_ENABLED(Any p0) { return invoke<BOOL>(0x52B9A693, p0); } // 0x52B9A693
   static void SET_CAMERA_FOCUS_PLAYER_INPUT_DISABLED(Any p0, Any p1) { invoke<Void>(0x6FDE0A8C, p0, p1); } // 0x6FDE0A8C
   static void SET_CAMERA_FOCUS_PLAYER_INVULNERABLE(Any p0, Any p1) { invoke<Void>(0x4A3AE626, p0, p1); } // 0x4A3AE626
   static void SET_CAMERA_FOCUS_PROMPT_TEXT(Any p0, Any p1) { invoke<Void>(0x21633E5F, p0, p1); } // 0x21633E5F
   static void SET_CAMERA_FOCUS_OBJECT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x48C3D85A, p0, p1, p2, p3, p4, p5); } // 0x48C3D85A
}

namespace CHALLENGE
{
   static void UI_CHALLENGE_CREATE(Any p0, Any p1, Any p2) { invoke<Void>(0x1EB9AF29, p0, p1, p2); } // 0x1EB9AF29
   static void UI_CHALLENGE_SET_DESCRIPTION(Any p0, Any p1) { invoke<Void>(0x2A39FD8A, p0, p1); } // 0x2A39FD8A
   static int UI_CHALLENGE_SET_TITLE_TEXTURE(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xD5ED5FCB, p0, p1, p2, p3); } // 0xD5ED5FCB
   static void UI_CHALLENGE_SET_PROGRESS(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x10F5386D, p0, p1, p2, p3, p4); } // 0x10F5386D
   static void UI_CHALLENGE_SET_PROGRESS_DETAIL(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x9D9CDCE3, p0, p1, p2, p3); } // 0x9D9CDCE3
   static int UI_CHALLENGE_SET_TROPHY_TYPE(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x3731AC9F, p0, p1, p2, p3); } // 0x3731AC9F
   static void UI_CHALLENGE_SET_OBJECTIVE(Any p0, Any p1, Any p2) { invoke<Void>(0x9CF5C747, p0, p1, p2); } // 0x9CF5C747
   static int UI_CHALLENGE_SET_OBJECTIVE_STYLE(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x4A598723, p0, p1, p2, p3); } // 0x4A598723
   static int UI_CHALLENGE_SET_OBJECTIVE_STYLE_B(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x9272926C, p0, p1, p2, p3); } // 0x9272926C
   static int UI_CHALLENGE_SET_COLUMN_HEADER(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xAFC9071D, p0, p1, p2, p3); } // 0xAFC9071D
   static int UI_CHALLENGE_SET_TIME_HEADER(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x761A6750, p0, p1, p2, p3); } // 0x761A6750
   static int UI_CHALLENGE_SET_TIME_INFO(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xC201524D, p0, p1, p2, p3); }  // 0xC201524D
   static void UI_CHALLENGE_MAKE_CURRENT(Any p0) { invoke<Void>(0x04A3022E, p0); } // 0x04A3022E
}

namespace COMBAT
{
   static void COMBAT_CLASS_AI_CLEAR_ALL_ATTRIBS(Any p0) { invoke<Void>(0x13FA7128, p0); } // 0x13FA7128
   static int COMBAT_CLASS_AI_GET_ATTRIB_BOOL(Any p0, Any p1) { return invoke<int>(0xE39B4D25, p0, p1); } // 0xE39B4D25
   static int COMBAT_CLASS_AI_GET_ATTRIB_FLOAT(Any p0, Any p1) { return invoke<int>(0xAAD75024, p0, p1); } // 0xAAD75024
   static int COMBAT_CLASS_AI_GET_RANGE_ACCURACY(Any p0) { return invoke<int>(0x983DB127, p0); } // 0x983DB127
   static void COMBAT_CLASS_AI_SET_ATTRIB_BOOL(Any p0, Any p1, Any p2) { invoke<Void>(0x69C5ADD2, p0, p1, p2); } // 0x69C5ADD2
   static void COMBAT_CLASS_AI_SET_ATTRIB_FLOAT(Any p0, Any p1, Any p2) { invoke<Void>(0x80D51606, p0, p1, p2); } // 0x80D51606
   static void COMBAT_CLASS_AI_SET_FIGHT_ATTACK_DISTANCE(Any p0, Any p1, Any p2) { invoke<Void>(0x6389CF4B, p0, p1, p2); } // 0x6389CF4B
   static void COMBAT_CLASS_AI_SET_FIGHT_DESIRED_DISTANCE(Any p0, Any p1, Any p2) { invoke<Void>(0xE20587E7, p0, p1, p2); } // 0xE20587E7
   static int COMBAT_CLASS_AI_SET_FIGHT_TIME_BETWEEN_ATTACKS_MULTIPLIER(Any p0, float p1) { return invoke<int>(0x0EF1436B, p0, p1); } // 0x0EF1436B
   static void COMBAT_CLASS_AI_SET_FIGHT_TIME_BETWEEN_ATTACKS(Any p0, Any p1) { invoke<Void>(0x1EF0E419, p0, p1); } // 0x1EF0E419
   static void COMBAT_CLASS_AI_SET_FRIENDLY_FIRE_CONSIDERATION(Any p0, Any p1) { invoke<Void>(0xF1454677, p0, p1); } // 0xF1454677
   static void COMBAT_CLASS_AI_SET_RANGE_ACCURACY(Any p0, Any p1) { invoke<Void>(0x60B705A5, p0, p1); } // 0x60B705A5
   static void COMBAT_CLASS_AI_SET_RANGE_BETWEEN_BURSTS_DELAY(Any p0, Any p1, Any p2) { invoke<Void>(0xC30DB881, p0, p1, p2); } // 0xC30DB881
   static void COMBAT_CLASS_NAME_REGISTER_INT(Any p0, Any p1) { invoke<Void>(0x8DE6AF29, p0, p1); } // 0x8DE6AF29
   static int _0x629E2E88() { return invoke<int>(0x629E2E88); } // 0x629E2E88
   static int COMBAT_CLASS_REQUEST_GET_ACTOR() { return invoke<int>(0x0EDD5D43); } // 0x0EDD5D43
   static int _0x76478D6E() { return invoke<int>(0x76478D6E); }   // 0x76478D6E
   static void COMBAT_CLASS_REQUEST_COMPLETED() { invoke<Void>(0xE66AD206); } // 0xE66AD206
   static void _0xAD3877AF(Any p0) { invoke<Void>(0xAD3877AF, p0); } // 0xAD3877AF
   static void AI_COMBAT_SET_NEW_STATE_MACHINE_ENABLED(Any p0, Any p1) { invoke<Void>(0x7F73E1E8, p0, p1); } // 0x7F73E1E8
}

namespace COVER
{
   static int FIND_NEAREST_COVER_LOCATION(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x50AE988A, p0, p1, p2, p3, p4); } // 0x50AE988A
   static int _GET_COVER_LOCATIONS_IN_VOLUME(Any p0, Any p1, Any p2, float p3, float p4, Any p5, Any p6, Any p7) { return invoke<int>(0x9265B24B, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x9265B24B
   static int _0x8DFF31DF(Any p0, Any p1) { return invoke<int>(0x8DFF31DF, p0, p1); } // 0x8DFF31DF
   static float GET_COVER_LOCATION_DIRECTION(Any p0) { return invoke<float>(0x620178B3, p0); } // 0x620178B3
   static int GET_COVER_LOCATION_POSITION(Any p0, Any p1) { return invoke<int>(0xA7F84C2F, p0, p1); } // 0xA7F84C2F
   static int _0x90AD2C2D(Any p0) { return invoke<int>(0x90AD2C2D, p0); } // 0x90AD2C2D
   static int ADD_AI_COVERSET_FOR_PROPSET(Any p0) { return invoke<int>(0x6BA6BC9B, p0); } // 0x6BA6BC9B
}

namespace CURVE
{
   static int ENABLE_CURVE(Any p0, Any p1) { return invoke<int>(0x0C46DAB3, p0, p1); } // 0x0C46DAB3
   static int _0xA5FF6076(Any p0, float p1, float p2, float p3, float p4) { return invoke<int>(0xA5FF6076, p0, p1, p2, p3, p4); } // 0xA5FF6076
   static int _0x0E018669(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<int>(0x0E018669, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x0E018669
   static int _0x8C37CA1A(Any p0, Any p1) { return invoke<int>(0x8C37CA1A, p0, p1); } // 0x8C37CA1A
   static int _0x9398BE8F(Any p0) { return invoke<int>(0x9398BE8F, p0); } // 0x9398BE8F
   static int _0x8E551A7C(Any p0) { return invoke<int>(0x8E551A7C, p0); } // 0x8E551A7C
   static int _0xBADCF1E9(Any p0) { return invoke<int>(0xBADCF1E9, p0); } // 0xBADCF1E9
   static int _0xE531DCAE(Any p0, Any p1, Any p2) { return invoke<int>(0xE531DCAE, p0, p1, p2); } // 0xE531DCAE
   static int _0xB4D1D8A3(Any p0, Any p1) { return invoke<int>(0xB4D1D8A3, p0, p1); } // 0xB4D1D8A3
   static int _0xBD4E48A6(Any p0, Any p1) { return invoke<int>(0xBD4E48A6, p0, p1); } // 0xBD4E48A6
   static int _0x90B514B9(Any p0, Any p1, Any p2) { return invoke<int>(0x90B514B9, p0, p1, p2); } // 0x90B514B9
   static int _0x4F8FAF8F(Any p0, Any p1) { return invoke<int>(0x4F8FAF8F, p0, p1); } // 0x4F8FAF8F
   static void _0x04D89A35(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x04D89A35, p0, p1, p2, p3, p4); } // 0x04D89A35
   static void _0x19D652F9(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x19D652F9, p0, p1, p2, p3); } // 0x19D652F9
   static int _0x39DA0B3A(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x39DA0B3A, p0, p1, p2, p3); } // 0x39DA0B3A
   static int _0x49D2C1DA(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x49D2C1DA, p0, p1, p2, p3); } // 0x49D2C1DA
   static void RELEASE_CURVE(Any p0) { invoke<Void>(0x8270CE81, p0); } // 0x8270CE81
   static int GET_CURVE_TYPE(Any p0) { return invoke<int>(0xE1007398, p0); } // 0xE1007398
   static Any GET_CURVE_NAME(Any p0) { return invoke<Any>(0x9A933060, p0); } // 0x9A933060
   static Any GET_CURVE_POINT(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x1CDF1EC4, p0, p1, p2, p3); } // 0x1CDF1EC4
   static void SET_CURVE_ACTIVE(Any p0, Any p1) { invoke<Void>(0x74460602, p0, p1); } // 0x74460602
   static void SET_CURVE_WEIGHT(Any p0, Any p1) { invoke<Void>(0xA7BB9E5E, p0, p1); } // 0xA7BB9E5E
   static int _0xF0441E47(Any p0, Any p1, Any p2) { return invoke<int>(0xF0441E47, p0, p1, p2); } // 0xF0441E47
}

namespace CUTSCENE
{
   static int _CUTSCENE_MANAGER_SCRIPT_DOES_NOT_EXIST(Any p0) { return invoke<int>(0xD89902F1, p0); } // 0xD89902F1
   static int CUTSCENE_MANAGER_LOAD_CUTFILE(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x99D215B4, p0, p1, p2, p3); } // 0x99D215B4
   static int _0xA6CFA220() { return invoke<int>(0xA6CFA220); } // 0xA6CFA220
   static const char* _0x0FE90DCB() { return invoke<const char*>(0x0FE90DCB); } // 0x0FE90DCB
   static int _0x7716B12B() { return invoke<int>(0x7716B12B); }  // 0x7716B12B
   static int CUTSCENE_MANAGER_LOAD_CUTSCENE(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0xFD300D15, p0, p1, p2, p3, p4); } // 0xFD300D15
   static int _0xEDF1D0B4() { return invoke<int>(0xEDF1D0B4); }  // 0xEDF1D0B4
   static int CUTSCENE_MANAGER_UNLOAD_CUTSCENE() { return invoke<int>(0xE7F781B8); } // 0xE7F781B8
   static int CUTSCENE_MANAGER_PLAY_CUTSCENE() { return invoke<int>(0x98A9AC9E); } // 0x98A9AC9E
   static int CUTSCENE_MANAGER_STOP_CUTSCENE(Any p0, Any p1) { return invoke<int>(0x9E6CAD1D, p0, p1); } // 0x9E6CAD1D
   static int _0xA61FA36B() { return invoke<int>(0xA61FA36B); }// 0xA61FA36B
   static int _0xDE339CE1() { return invoke<int>(0xDE339CE1); } // 0xDE339CE1
   static int _0x82F80FEA(Any p0) { return invoke<int>(0x82F80FEA, p0); } // 0x82F80FEA
   static int _0xCBE7BE6A(Any p0) { return invoke<int>(0xCBE7BE6A, p0); } // 0xCBE7BE6A
   static int _0x9E6A776F(Any p0, Any p1) { return invoke<int>(0x9E6A776F, p0, p1); } // 0x9E6A776F
   static int _0x47FAE768(float p0, float p1, float p2, float p3) { return invoke<int>(0x47FAE768, p0, p1, p2, p3); } // 0x47FAE768
   static int _0x93F356F4() { return invoke<int>(0x93F356F4); } // 0x93F356F4
   static int _0xE808BFFB(Any p0) { return invoke<int>(0xE808BFFB, p0); } // 0xE808BFFB
   static const char* _0xE0BE8235(const char* p0) { return invoke<const char*>(0xE0BE8235, p0); } // 0xE0BE8235
   static BOOL _0x7653788C() { return invoke<BOOL>(0x7653788C); } // 0x7653788C
   static void _0x98D0F458() { invoke<Void>(0x98D0F458); } // 0x98D0F458
   static float _0xAC5043C5() { return invoke<float>(0xAC5043C5); } // 0xAC5043C5
   static int _0x7263860F() { return invoke<int>(0x7263860F); } // 0x7263860F
   static int _0x2DB208A1() { return invoke<int>(0x2DB208A1); } // 0x2DB208A1
   static int _0x1501F924() { return invoke<int>(0x1501F924); } // 0x1501F924
   static int _0xC677BF51() { return invoke<int>(0xC677BF51); } // 0xC677BF51
   static int _0xC2B5BDDF() { return invoke<int>(0xC2B5BDDF); } // 0xC2B5BDDF
   static int _0xA5691922() { return invoke<int>(0xA5691922); } // 0xA5691922
   static int _0xC6557710(Any p0) { return invoke<int>(0xC6557710, p0); } // 0xC6557710
   static int _0xED0BA189(Any p0, Any p1) { return invoke<int>(0xED0BA189, p0, p1); } // 0xED0BA189
   static int _0xEA8E6112(Any p0) { return invoke<int>(0xEA8E6112, p0); } // 0xEA8E6112
   static int _0xB2F2A7F2(Any p0, Any p1, Any p2) { return invoke<int>(0xB2F2A7F2, p0, p1, p2); } // 0xB2F2A7F2
   static int _0x9410D992(Any p0, Any p1, Any p2) { return invoke<int>(0x9410D992, p0, p1, p2); } // 0x9410D992
   static int _0xD9E4A8DA() { return invoke<int>(0xD9E4A8DA); } // 0xD9E4A8DA
   static int _0xEBAB5F62(Any p0) { return invoke<int>(0xEBAB5F62, p0); } // 0xEBAB5F62
   static int _0x5DB05BBC(Any p0) { return invoke<int>(0x5DB05BBC, p0); } // 0x5DB05BBC
   static int _0x3BDB2ADF(Any* p0, Any p1) { return invoke<int>(0x3BDB2ADF, p0, p1); } // 0x3BDB2ADF
   static int _0x79C748BE(Any p0, Any p1, Any p2) { return invoke<int>(0x79C748BE, p0, p1, p2); } // 0x79C748BE
   static int _0xA56DCCF2(Any p0, Any p1, Any p2) { return invoke<int>(0xA56DCCF2, p0, p1, p2); } // 0xA56DCCF2
   static BOOL CUTSCENE_MANAGER_HIDE_ACTOR(Any p0) { return invoke<BOOL>(0x3D014AB1, p0); } // 0x3D014AB1
   static int CUTSCENE_MANAGER_SHOW_ACTOR(Any p0) { return invoke<int>(0xB550D120, p0); } // 0xB550D120
   static int CUTSCENE_MANAGER_GET_INITIAL_STREAMING_LOAD_SCENE_EXT(Any p0, Any p1) { return invoke<int>(0xD79C7D6A, p0, p1); } // 0xD79C7D6A
   static int _0x5C553565(Any p0, Any p1) { return invoke<int>(0x5C553565, p0, p1); } // 0x5C553565
   static void _0xB0479CB8(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xB0479CB8, p0, p1, p2, p3, p4, p5); } // 0xB0479CB8
   static int _0x35DBDD67(Any p0, Any p1) { return invoke<int>(0x35DBDD67, p0, p1); } // 0x35DBDD67 //Overrode with in Cutscene
   static int _0x250232CF(Any p0, Any p1) { return invoke<int>(0x250232CF, p0, p1); } // 0x250232CF //Overrode with in Cutscene
   static void _0x7007019D(Any p0, Any p1) { invoke<Void>(0x7007019D, p0, p1); } // 0x7007019D
   static int _0x24F97294() { return invoke<int>(0x24F97294); } // 0x24F97294
   static const char* _0xDE79FA4E() { return invoke<const char*>(0xDE79FA4E); } // 0xDE79FA4E
   static void _0x2B45FADE() { invoke<Void>(0x2B45FADE); } // 0x2B45FADE
   static void _0x50A2051C(Any p0) { invoke<Void>(0x50A2051C, p0); } // 0x50A2051C
}

namespace DECAL
{
   static void _0xA5A6A3E3(Any p0, Any p1, Any p2) { invoke<Void>(0xA5A6A3E3, p0, p1, p2); } // 0xA5A6A3E3
   static int _0x3736FF43() { return invoke<int>(0x3736FF43); } // 0x3736FF43
   static int _0x065B4197() { return invoke<int>(0x065B4197); } // 0x065B4197
   static void CLEAR_DECALS() { invoke<Void>(0x43939FD8); } // 0x43939FD8
   static void CREATE_DECAL(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x21588246, p0, p1, p2, p3, p4, p5, p6); } // 0x21588246
   static void CREATE_DIRECTION_DECAL(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0xFB4CFBA0, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xFB4CFBA0
   static void _0x7BCE4845(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { invoke<Void>(0x7BCE4845, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0x7BCE4845
   static int _0x9E54C297(Any p0, Any p1, float p2, float p3, float p4, float p5, float p6, float p7) { return invoke<int>(0x9E54C297, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x9E54C297
   static void AT_FIRED_LAST(Any p0, Any p1, Any p2) { invoke<Void>(0x013A0D25, p0, p1, p2); } // 0x013A0D25
   static void _0x1182C34F(Any p0) { invoke<Void>(0x1182C34F, p0); }// 0x1182C34F
   static void _0xD0FB6AF0(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xD0FB6AF0, p0, p1, p2, p3); } // 0xD0FB6AF0
   static void _0xC00F8181(Any p0, float p1) { invoke<Void>(0xC00F8181, p0, p1); } // 0xC00F8181
   static void _0x4897DD37(Any p0) { invoke<Void>(0x4897DD37, p0); } // 0x4897DD37
   static void _0x6E946AF8(Any p0) { invoke<Void>(0x6E946AF8, p0); } // 0x6E946AF8
   static void _0xB6CA7EBF(Any p0) { invoke<Void>(0xB6CA7EBF, p0); } // 0xB6CA7EBF
   static void RESET_ANALOG_POSITIONS(Any p0, Any p1) { invoke<Void>(0x4710FD93, p0, p1); } // 0x4710FD93
   static float _0x6A0A241A(Any p0) { return invoke<float>(0x6A0A241A, p0); } // 0x6A0A241A
   static void CANCEL_DEADEYE() { invoke<Void>(0xCB0BDCE9); } // 0xCB0BDCE9
   static void _0xFA43DCC5(Any p0) { invoke<Void>(0xFA43DCC5, p0); } // 0xFA43DCC5
   static int _0xEC906A7A(float p0) { return invoke<int>(0xEC906A7A, p0); } // 0xEC906A7A
   static int _0xC9FCD3EC(float p0) { return invoke<int>(0xC9FCD3EC, p0); } // 0xC9FCD3EC
   static void DOF_PUSH() { invoke<Void>(0xF665F9D1); } // 0xF665F9D1
   static void DOF_POP() { invoke<Void>(0x5EBE0C41); } // 0x5EBE0C41
   static void DOF_SET(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xEA8964CC, p0, p1, p2, p3); } // 0xEA8964CC
   static void _0x47A8DDED(Any p0) { invoke<Void>(0x47A8DDED, p0); } // 0x47A8DDED
   static int _0x3B32AB84(Any p0, float p1, float p2, float p3) { return invoke<int>(0x3B32AB84, p0, p1, p2, p3); } // 0x3B32AB84
   static void REMOVE_GLOW_INDICATOR(Any p0) { invoke<Void>(0xCBDD5832, p0); } // 0xCBDD5832
   static void CREATE_OBJECT_GLOW(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x1065D334, p0, p1, p2, p3, p4, p5); } // 0x1065D334
   static void DESTROY_OBJECT_GLOW(Any p0) { invoke<Void>(0xFC261530, p0); } // 0xFC261530
   static void CLEAR_TUMBLEWEEDS() { invoke<Void>(0x8852F896); } // 0x8852F896
   static void ALLOW_TUMBLEWEEDS(Any p0) { invoke<Void>(0xFDE8DFCE, p0); } // 0xFDE8DFCE
   static int _0x1EE7153B(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x1EE7153B, p0, p1, p2, p3); } // 0x1EE7153B
   static int _0x5685A440(Any p0, float p1, float p2, float p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<int>(0x5685A440, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x5685A440
   static int _0x50904C66(Any p0, float p1, float p2, float p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<int>(0x50904C66, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x50904C66
   static void CLEAR_CHARACTER_BLOOD() { invoke<Void>(0x1A676EDF); } // 0x1A676EDF
   static void CLEAR_PLAYER_BLOOD() { invoke<Void>(0x807C9D01); } // 0x807C9D01
   static void _0x9D9E093E(Any p0) { invoke<Void>(0x9D9E093E, p0); } // 0x9D9E093E
   static int _0x32F2D6F1(Any p0) { return invoke<int>(0x32F2D6F1, p0); } // 0x32F2D6F1
   static void BURN_ACTOR(Any p0, Any p1, Any p2) { invoke<Void>(0xA257C16D, p0, p1, p2); } // 0xA257C16D
   static int _0x3627F773(Any p0, int a2) { return invoke<int>(0x3627F773); } // 0x3627F773
   static int _0x48123591(Any p0) { return invoke<int>(0x48123591, p0); } // 0x48123591
   static void _0xA0AE0C98(Any p0, Any p1) { invoke<Void>(0xA0AE0C98, p0, p1); } // 0xA0AE0C98
}

namespace DECORATOR
{
   static int _0x9AC89564(Any p0, Any p1, Any p2) { return invoke<int>(0x9AC89564, p0, p1, p2); } // 0x9AC89564
   static int _0xFAC315B7(Any p0, Any p1, Any p2) { return invoke<int>(0xFAC315B7, p0, p1, p2); } // 0xFAC315B7
   static int _0x1F003E6C(Any p0, Any p1, Any p2) { return invoke<int>(0x1F003E6C, p0, p1, p2); } // 0x1F003E6C
   static Any DECOR_SET_BOOL(Actor actor, const char* propertyName, BOOL value) { return invoke<Any>(0x8E101F5C, actor, propertyName, value); } // 0x8E101F5C
   static Any DECOR_SET_FLOAT(Any p0, Any p1, Any p2) { return invoke<Any>(0xBC7BD5CB, p0, p1, p2); } // 0xBC7BD5CB
   static Any DECOR_SET_INT(Any p0, Any p1, Any p2) { return invoke<Any>(0xDB718B21, p0, p1, p2); } // 0xDB718B21
   static Any DECOR_SET_VECTOR(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xAAED0B69, p0, p1, p2, p3, p4); } // 0xAAED0B69
   static Any DECOR_SET_STRING(Any p0, Any p1, Any p2) { return invoke<Any>(0x53D3FB4A, p0, p1, p2); } // 0x53D3FB4A
   static Any DECOR_SET_OBJECT(Any p0, Any p1, Any p2) { return invoke<Any>(0x44F8BCC5, p0, p1, p2); } // 0x44F8BCC5
   static int DECOR_CHECK_STRING(Actor actor, const char* propertyName, const char* eventName) { return invoke<int>(0xEDF99C77, actor, propertyName, eventName); } // 0xEDF99C77
   static int DECOR_GET_STRING_HASH(Any p0, Any p1) { return invoke<int>(0x6A0FE2A0, p0, p1); } // 0x6A0FE2A0
   static int DECOR_GET_BOOL(Any p0, Any p1) { return invoke<int>(0xDBCE51E0, p0, p1); } // 0xDBCE51E0
   static int DECOR_GET_FLOAT(Any p0, Any p1) { return invoke<int>(0x8DE5382F, p0, p1); } // 0x8DE5382F
   static int DECOR_GET_INT(Any p0, Any p1) { return invoke<int>(0xDDDE59B5, p0, p1); } // 0xDDDE59B5
   static int DECOR_GET_VECTOR(Any p0, Any p1, Any p2) { return invoke<int>(0x56E84C59, p0, p1, p2); } // 0x56E84C59
   static int DECOR_GET_OBJECT(Any p0, Any p1) { return invoke<int>(0x24F2E859, p0, p1); } // 0x24F2E859
   static int DECOR_CHECK_EXIST(Actor actor, const char* propertyName) { return invoke<int>(0xA0773F5C, actor, propertyName); } // 0xA0773F5C
   static int DECOR_REMOVE(Actor actor, const char* propertyName) { return invoke<int>(0xE0E2640B, actor, propertyName); } // 0xE0E2640B
   static int DECOR_REMOVE_ALL(Any p0) { return invoke<int>(0xFDB9E349, p0); } // 0xFDB9E349
}

namespace DLC
{
   static const char* _DLC_PREINIT() { return invoke<const char*>(0x0728B211); } // 0x0728B211
   static int _DLC_INIT() { return invoke<int>(0xEC86DB0E); } // 0xEC86DB0E
   static int _DLC_FRAGMENT(const char* p0) { return invoke<int>(0x57D9950B, p0); } // 0x57D9950B
   static int _DLC_CLIST(Any p0, Any p1) { return invoke<int>(0xF4D0807E, p0, p1); } // 0xF4D0807E
   static BOOL _0x853F71F6(Any p0) { return invoke<int>(0x853F71F6, p0); } // 0x853F71F6
}

namespace DOOR
{
   static Any FIND_NEAREST_DOOR(Any p0, Any p1) { return invoke<Any>(0x9CB5372B, p0, p1); } // 0x9CB5372B
   static int GET_DOOR_FROM_OBJECT(Any p0) { return invoke<int>(0x9CE0AA24, p0); } // 0x9CE0AA24
   static BOOL IS_DOOR_VALID(Any p0) { return invoke<BOOL>(0x7F0F079B, p0); } // 0x7F0F079B
   static BOOL IS_DOOR_LOCKED(Any p0) { return invoke<BOOL>(0x19FB9518, p0); } // 0x19FB9518
   static void SET_DOOR_LOCK(Any p0, Any p1) { invoke<Void>(0x184924E2, p0, p1); } // 0x184924E2
   static BOOL IS_DOOR_CLOSED(Any p0) { return invoke<BOOL>(0x48659CD7, p0); } // 0x48659CD7
   static BOOL IS_DOOR_OPENED(Any p0) { return invoke<BOOL>(0x211DD9D2, p0); } // 0x211DD9D2
   static BOOL IS_DOOR_OPENING(Any p0) { return invoke<BOOL>(0x52BB0836, p0); } // 0x52BB0836
   static BOOL IS_DOOR_CLOSING(Any p0) { return invoke<BOOL>(0xCBA9F32C, p0); } // 0xCBA9F32C
   static void SET_DOOR_AUTO_CLOSE(Any p0, Any p1) { invoke<Void>(0xD3300956, p0, p1); } // 0xD3300956
   static int SET_DOOR_CURRENT_SPEED(Any p0, Any p1, Any p2) { return invoke<int>(0x5BCFC899, p0, p1, p2); } // 0x5BCFC899
   static void OPEN_DOOR(Any p0, Any p1, Any p2) { invoke<Void>(0x30503E81, p0, p1, p2); } // 0x30503E81
   static void OPEN_DOOR_DIRECTION(Any p0, Any p1) { invoke<Void>(0xAACB4435, p0, p1); } // 0xAACB4435
   static void OPEN_DOOR_FAST(Any p0, Any p1) { invoke<Void>(0xCF89BC95, p0, p1); } // 0xCF89BC95
   static void OPEN_DOOR_DIRECTION_FAST(Any p0, Any p1) { invoke<Void>(0xBA51D02E, p0, p1); } // 0xBA51D02E
   static void CLOSE_DOOR(Any p0, Any p1) { invoke<Void>(0x075B1736, p0, p1); } // 0x075B1736
   static void CLOSE_DOOR_FAST(Any p0) { invoke<Void>(0xFEEC0767, p0); } // 0xFEEC0767
   static int _0x3B25299D(Any p0) { return invoke<int>(0x3B25299D, p0); } // 0x3B25299D
   static int SET_DOOR_LOCK_VISIBLE(Any p0) { return invoke<int>(0x468DDDB3, p0); } // 0x468DDDB3
   static BOOL IS_DOOR_OPEN_IN_DIRECTION(Any p0, Any p1) { return invoke<BOOL>(0xDAD47AE6, p0, p1); } // 0xDAD47AE6
}

namespace ELEMENT
{
   static void _0x598815BD(float p0) { invoke<Void>(0x598815BD, p0); } // 0x598815BD
   static const char* _0xD1C91A7F(float p0, float p1, float p2, float p3) { return invoke<const char*>(0xD1C91A7F, p0, p1, p2, p3); } // 0xD1C91A7F
   static int _0x7E0CDD87() { return invoke<int>(0x7E0CDD87); } // 0x7E0CDD87
   static int _0xE6C1DBD9(Any p0) { return invoke<int>(0xE6C1DBD9, p0); } // 0xE6C1DBD9
   static int _0x00EF33EF() { return invoke<int>(0x00EF33EF); } // 0x00EF33EF
   static Any _0xDF505043(Any result) { return invoke<Any>(0xDF505043, result); }// 0xDF505043
   static void _0xE613AE52(float p0) { invoke<Void>(0xE613AE52, p0); } // 0xE613AE52
   static void _0x84F3DD81(float p0, float p1) { invoke<Void>(0x84F3DD81, p0, p1); } // 0x84F3DD81
   static Any _0xF55B50ED(Any result) { return invoke<Any>(0xF55B50ED, result); } // 0xF55B50ED
   static int _0x6336182D(Any p0) { return invoke<int>(0x6336182D, p0); } // 0x6336182D
   static void _0x3A6960B2(float p0) { invoke<Void>(0x3A6960B2, p0); } // 0x3A6960B2
}

namespace EVENT
{
   static BOOL IS_EVENT_VALID(Any p0) { return invoke<BOOL>(0x4911EB99, p0); } // 0x4911EB99
   static Object GET_EVENT_FROM_OBJECT(Object p0) { return invoke<Object>(0x184BD1BC, p0); } // 0x184BD1BC
   static int* GET_OBJECT_FROM_EVENT(int* p0, Any p1) { return invoke<int*>(0xB64DDA6F, p0, p1); } // 0xB64DDA6F
   static int COPY_EVENT(Any p0, Any p1) { return invoke<int>(0xF7DA8F09, p0, p1); } // 0xF7DA8F09
   static Layout GET_EVENT_LAYOUT() { return invoke<Layout>(0xD938B523); } // 0xD938B523
   static int GET_EVENT_TYPE(Any p0) { return invoke<int>(0x6D660453, p0); } // 0x6D660453
   static int _0xE2ED95CC(Any p0) { return invoke<int>(0xE2ED95CC, p0); } // 0xE2ED95CC
   static int _0xBDD4D4D5(Any p0) { return invoke<int>(0xBDD4D4D5, p0); } // 0xBDD4D4D5
   static int GET_EVENT_PERPETRATOR(Any p0) { return invoke<int>(0x0B5431C9, p0); } // 0x0B5431C9
   static int _ADD_EVENT_RESPONSE(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x17CF885F, p0, p1, p2, p3); } // 0x17CF885F
   static int _ADD_RANGED_EVENT_RESPONSE(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x8DF144C2, p0, p1, p2, p3, p4); } // 0x8DF144C2
   static int REMOVE_EVENT_RESPONSE(Any p0, Any p1, Any p2) { return invoke<int>(0xFEE731AF, p0, p1, p2); } // 0xFEE731AF
   static void _0x85D62384() { invoke<Void>(0x85D62384); } // 0x85D62384
   static void _0xFB227D11(Any p0) { invoke<Void>(0xFB227D11, p0); } // 0xFB227D11
   static int GET_EVENT_TIME(Any p0) { return invoke<int>(0x82112B85, p0); } // 0x82112B85
   static int _GET_ITERATION_SET(int setId) { return invoke<int>(0xBC58F1EA, setId); }
   static int CREATE_EVENT_TRAP(Any p0, Any p1, Any p2) { return invoke<int>(0x24C18749, p0, p1, p2); } // 0x24C18749
   static void _0x88943B5B(Any p0, Any p1) { invoke<Void>(0x88943B5B, p0, p1); } // 0x88943B5B
   static int _0x3D2786E5(Any p0, float p1, float p2, float p3, float p4) { return invoke<int>(0x3D2786E5, p0, p1, p2, p3, p4); } // 0x3D2786E5
   static void _0x6B5DF46D(Any p0, Any p1) { invoke<Void>(0x6B5DF46D, p0, p1); } // 0x6B5DF46D
   static void _0x0AA5D947(Any p0, Any p1) { invoke<Void>(0x0AA5D947, p0, p1); } // 0x0AA5D947
   static void _0x1105FB64(Any p0, Any p1) { invoke<Void>(0x1105FB64, p0, p1); } // 0x1105FB64
   static void _0x08765C6B(Any p0, Any p1) { invoke<Void>(0x08765C6B, p0, p1); } // 0x08765C6B
   static void _0xDE9AA6E5(Any p0) { invoke<Void>(0xDE9AA6E5, p0); } // 0xDE9AA6E5
   static int _0x54F8EAA4(Any p0) { return invoke<int>(0x54F8EAA4, p0); } // 0x54F8EAA4
   static void _0xAA24E0CC(Any p0) { invoke<Void>(0xAA24E0CC, p0); } // 0xAA24E0CC
   static int _0x19F62133() { return invoke<int>(0x19F62133); } // 0x19F62133
   static int _0xB573FF63() { return invoke<int>(0xB573FF63); } // 0xB573FF63
   static int _0x586714AE() { return invoke<int>(0x586714AE); } // 0x586714AE
}

namespace EXPLOSION
{
   static void _CREATE_EXPLOSION(Vector3* position, const char* explosionName, BOOL p2, Vector3* damage, BOOL p4) { invoke<Void>(0xE7023D23, position, explosionName, p2, damage, p4); } // 0xE7023D23
   static const char* _SET_EXPLOSION(const char* p0) { return invoke<const char*>(0x651F6299, p0); } // 0x651F6299
}

namespace FACTION
{
   static Any RELOAD_FACTIONS(Any p0, Any p1, Any p2) { return invoke<Any>(0x40ABFD17, p0, p1, p2); } // 0x40ABFD17
   static Any RESET_FACTIONS(Any p0) { return invoke<Any>(0x28413943, p0); } // 0x28413943
   static Any GET_ACTOR_FACTION(Any p0) { return invoke<Any>(0x52E2A611, p0); } // 0x52E2A611
   static void SET_ACTOR_FACTION(Any p0, Any p1) { invoke<Void>(0xCC63951A, p0, p1); } // 0xCC63951A
   static BOOL IS_FACTION_VALID(Any p0) { return invoke<BOOL>(0x5E2F718D, p0); } // 0x5E2F718D
   static Any _0x22424394() { return invoke<Any>(0x22424394); } // 0x22424394
   static void SET_FACTION_IS_LAWFUL_TO_ATTACK(Any p0) { invoke<Void>(0xDCB960C5, p0); } // 0xDCB960C5
   static Any GET_FACTION_IS_LAWFUL_TO_ATTACK(Any p0) { return invoke<Any>(0xB58013D7, p0); } // 0xB58013D7
   static void _SET_FACTION_STATUS_ONEWAY(Any p0) { invoke<Void>(0xD771AF0B, p0); } // 0xD771AF0B
   static void _SET_FACTION_STATUS_TWOWAY(Any p0) { invoke<Void>(0x4C28B11E, p0); } // 0x4C28B11E
   static void _SET_FACTIONB_STATUS_TWOWAY(Any p0) { invoke<Void>(0x6118212B, p0); } // 0x6118212B
   static Any _0x902781BF(Any p0) { return invoke<Any>(0x902781BF, p0); } // 0x902781BF
   static Any _0xF9C5DC76(Any p0) { return invoke<Any>(0xF9C5DC76, p0); } // 0xF9C5DC76
   static void GET_FACTIONS_STATUS(Any p0) { invoke<Void>(0x8E56236D, p0); } // 0x8E56236D
   static void SET_FACTION_TO_FACTION_ACCURACY_SCALE_FACTOR(Any p0) { invoke<Void>(0x463F75F8, p0); } // 0x463F75F8
   static void SET_FACTION_TO_FACTION_DAMAGE_SCALE_FACTOR(Any p0) { invoke<Void>(0xA9A18E5A, p0); } // 0xA9A18E5A
   static void CLEAR_FACTION_STATUS_TO_INDIVIDUAL_ACTOR(Any p0) { invoke<Void>(0xEF639583, p0); } // 0xEF639583
   static Any GET_FACTION_STATUS_TO_INDIVIDUAL_ACTOR(Any p0) { return invoke<Any>(0x784398CB, p0); } // 0x784398CB
   static void SET_FACTION_STATUS_TO_INDIVIDUAL_ACTOR(Any p0) { invoke<Void>(0xBC44D31D, p0); } // 0xBC44D31D
}

namespace FACTION2
{
   static BOOL CAN_ANYONE_OF_FACTION_SEE_OBJECT(Any p0, Any p1) { return invoke<BOOL>(0x656D3D26, p0, p1); } // 0x656D3D26
}

namespace FIRE
{
   static int _0x9A93E7CA(float p0, float p1, float p2, float p3) { return invoke<int>(0x9A93E7CA, p0, p1, p2, p3); } // 0x9A93E7CA
   static int _0x59A7835E() { return invoke<int>(0x59A7835E); } // 0x59A7835E
   static int _0x25690082(Any p0) { return invoke<int>(0x25690082, p0); } // 0x25690082
   static int _0xE92C3435(Any p0) { return invoke<int>(0xE92C3435, p0); } // 0xE92C3435
   static int _0xDB86F53B(Any p0) { return invoke<int>(0xDB86F53B, p0); } // 0xDB86F53B
   static int _0x8BA565F7(Any p0) { return invoke<int>(0x8BA565F7, p0); } // 0x8BA565F7
   static int _0xB8E09389(Any p0) { return invoke<int>(0xB8E09389, p0); } // 0xB8E09389
   static int _0x9AA8A1B1(float p0, float p1, float p2, float p3) { return invoke<int>(0x9AA8A1B1, p0, p1, p2, p3); } // 0x9AA8A1B1
   static int _0x002B0698(float p0, float p1, float p2, float p3, Any p4, Any p5, Any p6) { return invoke<int>(0x002B0698, p0, p1, p2, p3, p4, p5, p6); } // 0x002B0698
   static int _0x57478561(Any p0) { return invoke<int>(0x57478561, p0); } // 0x57478561
   static int _0x39B0CFE5() { return invoke<int>(0x39B0CFE5); } // 0x39B0CFE5
   static void SET_VEHICLE_APPOINTMENT_TARGET() { invoke<Void>(0xDCAE6935); } // 0xDCAE6935
   static int _0x8CF15FCB() { return invoke<int>(0x8CF15FCB); } // 0x8CF15FCB
   static int _0x4A8066FB() { return invoke<int>(0x4A8066FB); } // 0x4A8066FB
   static int _0x1DDB57A6() { return invoke<int>(0x1DDB57A6); } // 0x1DDB57A6
   static int _0x88863344() { return invoke<int>(0x88863344); } // 0x88863344
   static int _0xE7371670() { return invoke<int>(0xE7371670); } // 0xE7371670
   static int _0x03E2B631() { return invoke<int>(0x03E2B631); } // 0x03E2B631
   static Any _0xCA840DBB(Any p0) { return invoke<Any>(0xCA840DBB, p0); }// 0xCA840DBB
   static int _0x4F3F3CA5() { return invoke<int>(0x4F3F3CA5); } // 0x4F3F3CA5
   static Any CREATE_FIRE_ON_OBJECT(Any p0) { return invoke<Any>(0xC587FA2B, p0); } // 0xC587FA2B
   static Any CREATE_FIRE_IN_VOLUME(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return invoke<Any>(0xD4799325, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xD4799325
   static void STOP_ALL_FIRES() { invoke<Void>(0x9544570A); } // 0x9544570A
   static void _0x8011737F() { invoke<Void>(0x8011737F); } // 0x8011737F
   static Any CREATE_FIRE_PROPERTY(Any* p0) { return invoke<Any>(0x5402321A, p0); } // 0x5402321A
   static Any* _0x2AC74780(Any p0) { return invoke<Any*>(0x2AC74780, p0); } // 0x2AC74780
   static void _0x466C02BA(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x466C02BA, p0, p1, p2, p3); } // 0x466C02BA
   static void _0xEC3A9EBB() { invoke<Void>(0xEC3A9EBB); } // 0xEC3A9EBB
   static int _0xADB3E8D9(Any p0, Any p1, Any p2) { return invoke<int>(0xADB3E8D9, p0, p1, p2); } // 0xADB3E8D9
   static int _BOUNDING_BOX(Any p0) { return invoke<int>(0x08D06543, p0); } // 0x08D06543
   static void ENABLE_WORLD_SECTOR(Any p0) { invoke<Void>(0xAD5613FD, p0); } // 0xAD5613FD
   static void DISABLE_WORLD_SECTOR(Any p0) { invoke<Void>(0xB511D087, p0); } // 0xB511D087
   static void ENABLE_CHILD_SECTOR(Any p0) { invoke<Void>(0x7ECE15BE, p0); } // 0x7ECE15BE
   static void DISABLE_CHILD_SECTOR(Any p0) { invoke<Void>(0x9E1AE585, p0); } // 0x9E1AE585
   static int HIDE_CHILD_SECTOR(Any p0) { return invoke<int>(0x4E6A78B5, p0); } // 0x4E6A78B5
   static int SHOW_CHILD_SECTOR(Any p0) { return invoke<int>(0x63A83655, p0); } // 0x63A83655
   static int FIRE_CREATE_HANDLE() { return invoke<int>(0xBBAE9CBD); } // 0xBBAE9CBD
   static BOOL _EXPLOSION_FIRE_FX(Any p0) { return invoke<BOOL>(0xA488E930, p0); } // 0xA488E930
   static void FIRE_RELEASE_HANDLE(Any p0, Any p1) { invoke<Void>(0xB14B936A, p0, p1); } // 0xB14B936A
   static int _RELEASE_INFINITE_FIRE_DESCRIPTOR(Any p0, Any p1, float p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return invoke<int>(0xD2BB733E, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0xD2BB733E
   static int _0x91396EB7(Any p0) { return invoke<int>(0x91396EB7, p0); } // 0x91396EB7
   static void FIRE_CREATE_ON_ACTOR(Actor actor, Any p1) { invoke<Void>(0x9679CF84, actor, p1); } // 0x9679CF84
   static int FIRE_CREATE_IN_VOLUME(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xB65ADFAC, p0, p1, p2, p3); } // 0xB65ADFAC
   static int FIRE_IS_ACTOR_ON_FIRE(Actor p0) { return invoke<int>(0x30C4CA99, p0); } // 0x30C4CA99
   static int _0x15001332() { return invoke<int>(0x15001332); } // 0x15001332
   static void FIRE_STOP_ON_ACTOR(Actor p0) { invoke<Void>(0xF635B9EA, p0); } // 0xF635B9EA
   static void _EXTINGUISH_FLAMES_IN_VOLUME(Any p0) { invoke<Void>(0x11A65FFB, p0); } // 0x11A65FFB
   static int FIRE_GET_OWNER(Any p0) { return invoke<int>(0x15683736, p0); } // 0x15683736
   static void FIRE_SET_OWNER(Any p0, Any p1) { invoke<Void>(0xE5C7E4C9, p0, p1); } // 0xE5C7E4C9
   static void _SET_FIRE_ATTACHED_DAMAGE_ALLOWED(Any p0, Any p1) { invoke<Void>(0x3D5D3B26, p0, p1); } // 0x3D5D3B26
   static void FIRE_SET_CONTROL_VOLUME(Any p0, Any p1) { invoke<Void>(0x03240324, p0, p1); } // 0x03240324
   static void FIRE_SET_MAX_FLAMES(Any p0, Any p1) { invoke<Void>(0xE5E04E83, p0, p1); } // 0xE5E04E83
   static void _SET_FIRE_TARGET_SIZE(Any p0, Any p1) { invoke<Void>(0x9C471E7D, p0, p1); } // 0x9C471E7D
   static void FIRE_SET_GROW_RATE(Any p0, Any p1) { invoke<Void>(0x1A82B949, p0, p1); } // 0x1A82B949
   static int FIRE_SET_DECAY_RATE(Any p0) { return invoke<int>(0x7906A950, p0); } // 0x7906A950
   static void FIRE_SET_EXPIRE_ALLOWED(Any p0, Any p1) { invoke<Void>(0x6471D75C, p0, p1); } // 0x6471D75C
   static void FIRE_SET_GROW_ALLOWED(Any p0, Any p1) { invoke<Void>(0x53895856, p0, p1); } // 0x53895856
   static int _0xDEE6523D(float p0, float p1, float p2, float p3) { return invoke<int>(0xDEE6523D, p0, p1, p2, p3); } // 0xDEE6523D
   static int COUNT_FLAMES_IN_VOLUME(Any p0) { return invoke<int>(0x3DD3E1EB, p0); } // 0x3DD3E1EB
   static int FIRE_ARE_ANY_FLAMES_IN_VOLUME(Any p0) { return invoke<int>(0x28DAED2A, p0); } // 0x28DAED2A
   static int _CHEAT_BLAZING_GUNS(BOOL toggle) { return invoke<int>(0x3F67DEDB, toggle); }
}

namespace GAME
{
   static void SET_DEBUG_DRAW(Any p0) { invoke<Void>(0x505A8057, p0); } // 0x505A8057
   static int _0xFF0B53EF() { return invoke<int>(0xFF0B53EF); } // 0xFF0B53EF
   static int _0x6DE957C6() { return invoke<int>(0x6DE957C6); } // 0x6DE957C6
   static void SCRIPT_BREAKPOINT(Any p0) { invoke<Void>(0xA81DABA3, p0); } // 0xA81DABA3
   static void _0x5AC72FCC(Any p0) { invoke<Void>(0x5AC72FCC, p0); } // 0x5AC72FCC Unused
   static void _0x9FEFA743(Any p0) { invoke<Void>(0x9FEFA743, p0); } // 0x9FEFA743
   static const char* GET_SCRIPT_NAME() { return invoke<const char*>(0x0BC52445); } // 0x0BC52445
   static const char* GET_SHORT_SCRIPT_NAME() { return invoke<const char*>(0x960DB7A5); } // 0x960DB7A5
   static void TERMINATE_THIS_SCRIPT() { invoke<Void>(0x245B6AB6); } // 0x245B6AB6
   static int GET_THIS_SCRIPT_ID() { return invoke<int>(0x9C424E0D); } // 0x9C424E0D
   static BOOL IS_SCRIPT_VALID(Any p0) { return invoke<BOOL>(0x45F7D589, p0); } // 0x45F7D589
   static BOOL DOES_SCRIPT_EXIST(Any p0) { return invoke<BOOL>(0xDEAB87AB, p0); } // 0xDEAB87AB
   static BOOL IS_EXITFLAG_SET() { return invoke<BOOL>(0x687ECC3C); } // 0x687ECC3C
   static int _0x4417C9F2(Any p0) { return invoke<int>(0x4417C9F2, p0); } // 0x4417C9F2
   static void _0x05719022(Any p0) { invoke<Void>(0x05719022, p0); } // 0x05719022
   static void TERMINATE_SCRIPT(Any p0) { invoke<Void>(0x60A7FF09, p0); } // 0x60A7FF09
   static void ADD_PERSISTENT_SCRIPT(Any p0) { invoke<Void>(0x2F109475, p0); } // 0x2F109475
   static void REMOVE_PERSISTENT_SCRIPT(Any p0) { invoke<Void>(0xC605E92F, p0); } // 0xC605E92F
   static int _0x4C48EA4D() { return invoke<int>(0x4C48EA4D); } // 0x4C48EA4D
   static int _0xD058BD70() { return invoke<int>(0xD058BD70); } // 0xD058BD70
   static int _0x26884138() { return invoke<int>(0x26884138); } // 0x26884138
   static void RAND_SET_SEED(Any p0) { invoke<Void>(0xC0C6245E, p0); }  // 0xC0C6245E
   static int RAND_INT_RANGE(int min, int max) { return invoke<int>(0xF8D0D165, min, max); } // 0xF8D0D165
   static float RAND_FLOAT_RANGE(float min, float max) { return invoke<Any>(0xCA6229BF, min, max); } // 0xCA6229BF
   static Any RAND_INT_RANGE_DIFFERENT(Any min, Any max, Any p2) { return invoke<float>(0x1D69F321, min, max, p2); } // 0x1D69F321
   static Any RAND_FLOAT_GAUSSIAN(Any p0) { return invoke<float>(0x5D934CCB, p0); } // 0x5D934CCB
   static void FILE_START_PATH(Any p0) { invoke<Void>(0x973BC454, p0); } // 0x973BC454
   static void _0x63CDBB01(Any p0) { invoke<Void>(0x63CDBB01, p0); } // 0x63CDBB01
   static void FILE_END_PATH() { invoke<Void>(0x9A202E1B); } // 0x9A202E1B
   static int _0x6F323C5F() { return invoke<int>(0x6F323C5F); } // 0x6F323C5F
   static float GET_X(Actor actor) { return invoke<float>(0x436CE75A, actor); } // 0x436CE75A
   static float GET_Y(Actor actor) { return invoke<float>(0x0B0FF6A1, actor); } // 0x0B0FF6A1
   static float GET_Z(Actor actor) { return invoke<float>(0x25A02BC1, actor); } // 0x25A02BC1
   static void _0x836466F8(Any p0) { invoke<Void>(0x836466F8, p0); } // 0x836466F8
   static void _0x4D629653(Any p0, Any p1, Any p2) { invoke<Void>(0x4D629653, p0, p1, p2); } // 0x4D629653
   static int _0x30A9FA0A(Any p0, Any p1) { return invoke<int>(0x30A9FA0A, p0, p1); } // 0x30A9FA0A
   static void VSCALE(Vector3* p0, float p1) { invoke<Void>(0x13530581, p0, p1); } // 0x13530581
   static int _0xF1A53C41(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xF1A53C41, p0, p1, p2, p3); } // 0xF1A53C41
   static void _0xF76F2BB3(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xF76F2BB3, p0, p1, p2, p3); } // 0xF76F2BB3
   static void _0x65DAA654(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x65DAA654, p0, p1, p2, p3, p4); } // 0x65DAA654
   static void _0x1BD78730(Any p0, Any p1, Any p2) { invoke<Void>(0x1BD78730, p0, p1, p2); } // 0x1BD78730
   static int _0x141201A3(float p0, float p1, float p2, float p3, float p4, float p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return invoke<int>(0x141201A3, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); }  // 0x141201A3
   static float FABS(float value) { return invoke<float>(0xACF9A5E4, value); } // 0xACF9A5E4
   static int ABS(int value) { return invoke<int>(0x5AABFA97, value); } // 0x5AABFA97
   static float SIN_DEGREE(float value) { return invoke<float>(0x55842354, value); } // 0x55842354
   static float COS_DEGREE(float value) { return invoke<float>(0x430207A4, value); } // 0x430207A4
   static float TAN_DEGREE(float value) { return invoke<float>(0x9BD37A3D, value); } // 0x9BD37A3D
   static float ATAN_DEGREE(float value) { return invoke<float>(0x69BE2817, value); } // 0x69BE2817
   static float ATAN2_DEGREE(float x, float y) { return invoke<float>(0x8A0D25F2, x, y); }// 0x8A0D25F2
   static float _0x9C40E671(float* p0) { return invoke<float>(0x9C40E671, p0); } // 0x9C40E671
   static float _0xADF7D54B(float* p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8) { return invoke<float>(0xADF7D54B, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xADF7D54B
   static int _0x3DD1DC3F(Any p0, Any p1) { return invoke<int>(0x3DD1DC3F, p0, p1); } // 0x3DD1DC3F
   static void _0x44986367(Any p0, Any p1) { invoke<Void>(0x44986367, p0, p1); } // 0x44986367
   static int _0xBB3CDF72(Any p0, float* p1, float* p2) { return invoke<int>(0xBB3CDF72, p0, p1, p2); } // 0xBB3CDF72
   static float GET_CURRENT_GAME_TIME() { return invoke<float>(0x5842B9D1); } // 0x5842B9D1
   static float _0xF83666A6() { return invoke<float>(0xF83666A6); } // 0xF83666A6
   static Any GET_SYSTEM_TIME() { return invoke<Any>(0x17CEE67A); } // 0x17CEE67A
   static int GET_TIMESTAMP() { return invoke<int>(0xD66B6C8E); } // 0xD66B6C8E
   static void GET_UTC_TIME(int* year, int* month, int* day, int* hour, int* minute, int* second) { invoke<Void>(0xC589CD7D, year, month, day, hour, minute, second); }// 0xC589CD7D
   static float _0x49F96787() { return invoke<float>(0x49F96787); }// 0x49F96787
   static float GET_PROFILE_TIME() { return invoke<float>(0x6E189771); } // 0x6E189771
   static float GET_LAST_FRAME_TIME() { return invoke<float>(0x59466B4D); } // 0x59466B4D
   static void LOG_MESSAGE(const char* message) { invoke<Void>(0x676167C3, message); } // 0x676167C3
   static void LOG_WARNING(const char* warning_message) { invoke<Void>(0xFD25473E, warning_message); } // 0xFD25473E
   static void LOG_ERROR(const char* error_message) { invoke<Void>(0x906C42FD, error_message); } // 0x906C42FD
   static int GET_TARGET_ACTOR() { return invoke<int>(0x0EF7427B); } // 0x0EF7427B
   static void GRINGO_SET_TARGET_OBJECT(Any p0, Any p1, Any p2) { invoke<Void>(0x00776356, p0, p1, p2); } // 0x00776356
   static int GET_TARGET_OBJECT() { return invoke<int>(0x533AD3F2); } // 0x533AD3F2
   static BOOL IS_GRINGO_VALID(Any p0) { return invoke<BOOL>(0x7C858A47, p0); } // 0x7C858A47
   static Any GET_GRINGO_ACTIVATION_SPHERE(Any p0) { return invoke<Any>(0xADA2EA30, p0); } // 0xADA2EA30
   static void _0xFD0AA999() { invoke<Void>(0xFD0AA999); } // 0xFD0AA999
   static void _0x71BE51F4() { invoke<Void>(0x71BE51F4); } // 0x71BE51F4
   static void GRINGO_ALLOW_ACTIVATION(Any p0, Any p1) { invoke<Void>(0x5E586923, p0, p1); } // 0x5E586923
   static int _0x52261CE0(Any p0) { return invoke<int>(0x52261CE0, p0); } // 0x52261CE0
   static BOOL _IS_KEY_DOWN(Any p0) { return invoke<BOOL>(0x358F874F, p0); } // 0x358F874F
   static BOOL _IS_KEY_PRESSED(Any p0) { return invoke<BOOL>(0xCBC97619, p0); } // 0xCBC97619
   static BOOL IS_BUTTON_DOWN(Any p0, int control, Any p2, Any p3) { return invoke<BOOL>(0xC3297B50, p0, control, p2, p3); } // 0xC3297B50
   static BOOL IS_BUTTON_PRESSED(Any p0, int control, Any p2, Any p3) { return invoke<BOOL>(0x7BCB3F15, p0, control, p2, p3); } // 0x7BCB3F15
   static BOOL IS_BUTTON_RELEASED(Any p0, int control, Any p2, Any p3) { return invoke<BOOL>(0xB04EB731, p0, control, p2, p3); } // 0xB04EB731
   static float GET_ANALOG_BUTTON_VALUE(Any p0, Any p1, Any p2) { return invoke<float>(0x23C9C74A, p0, p1, p2); } // 0x23C9C74A
   static float GET_STICK_X(int controller, BOOL isRightStick, Any p2) { return invoke<float>(0x9AAF7E28, controller, isRightStick, p2); } // 0x9AAF7E28
   static float GET_STICK_Y(int controller, BOOL isRightStick, Any p2) { return invoke<float>(0x7C6D41A4, controller, isRightStick, p2); } // 0x7C6D41A4
   static void _0x52B2F3F0(Any p0) { invoke<Void>(0x52B2F3F0, p0); } // 0x52B2F3F0
   static int _0xD4DEBC08(Any p0) { return invoke<int>(0xD4DEBC08, p0); } // 0xD4DEBC08
   static int _0xBEC2871A(Any p0) { return invoke<int>(0xBEC2871A, p0); } // 0xBEC2871A
   static int _0xEF4F4F20(Any p0) { return invoke<int>(0xEF4F4F20, p0); } // 0xEF4F4F20
   static int DEBUG_DRAW_VECTOR(Any p0, Any p1) { return invoke<int>(0xF7974EBA, p0, p1); } // 0xF7974EBA
   static void DEBUG_DRAW_LINE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x7C55C775, p0, p1, p2, p3); } // 0x7C55C775
   static int DEBUG_DRAW_SPHERE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<int>(0x4A1BAD30, p0, p1, p2, p4, p5, p6); } // 0x4A1BAD30
   static void DEBUG_DRAW_STRING() { invoke<Void>(0x993E45D8); } // 0x993E45D8
   static void _0x3C2D93C1(float x, float y, const char* text, float r, float g, float b, float a) { invoke<Void>(0x3C2D93C1, x, y, text, r, g, b, a); } // 0x3C2D93C1
   static void _0x73BE57AF(Any p0) { invoke<Void>(0x73BE57AF, p0); } // 0x73BE57AF
   static int _0xD1D88EB8(Any p0) { return invoke<int>(0xD1D88EB8, p0); } // 0xD1D88EB8 Debug
   static int _0x21E19CD5(Any p0) { return invoke<int>(0x21E19CD5, p0); } // 0x21E19CD5 Debug
   static int _0x1B6FE39B(Any p0) { return invoke<int>(0x1B6FE39B, p0); } // 0x1B6FE39B Debug
   static int _0xAAEBAC28(Any p0) { return invoke<int>(0xAAEBAC28, p0); } // 0xAAEBAC28 Debug
   static int _0x913A5CB6() { return invoke<int>(0x913A5CB6); } // 0x913A5CB6
   static int _0xD34F7B3A() { return invoke<int>(0xD34F7B3A); } // 0xD34F7B3A
   static int ACTOR_NOTE_USAGE_CHEAT() { return invoke<int>(0x191658C0); } // 0x191658C0
   static int _0x95132289() { return invoke<int>(0x95132289); } // 0x95132289
   static void _0xEB8325B3(Any p0) { invoke<Void>(0xEB8325B3, p0); } // 0xEB8325B3
   static int _0xD3FE15FB() { return invoke<int>(0xD3FE15FB); } // 0xD3FE15FB
   static int _0x32D1DEB0() { return invoke<int>(0x32D1DEB0); } // 0x32D1DEB0
   static void RETRIEVE_GAME_STATE(Any p0, Any p1, Any p2) { invoke<Void>(0x48FBB83D, p0, p1, p2); } // 0x48FBB83D
   static void STORE_GAME_STATE(Any p0, Any p1, Any p2) { invoke<Void>(0x800D6D89, p0, p1, p2); } // 0x800D6D89
   static void _0xE1124E00() { invoke<Void>(0xE1124E00); } // 0xE1124E00
   static void RESET_GAME() { invoke<Void>(0x07045C4E); } // 0x07045C4E
   static int _0x3B1B6407() { return invoke<int>(0x3B1B6407); } // 0x3B1B6407
   static int _GET_PARAM_VALUE(int* p0, Any p1, Any p2, Any p3) { return invoke<int>(0xC7612A79, p0, p1, p2, p3); } // 0xC7612A79
   static const char* _0x0B2D5E4B() { return invoke<const char*>(0x0B2D5E4B); } // 0x0B2D5E4B
   static Any LOAD_GAME(Any p0) { return invoke<Any>(0x7C5901EF, p0); } // 0x7C5901EF
   static Any LOAD_SOFT_SAVE(Any p0) { return invoke<Any>(0x0234F932, p0); } // 0x0234F932
   static Any SAVE_GAME(Any p0) { return invoke<Any>(0x09C5D8D5, p0); } // 0x09C5D8D5
   static void SAVE_SOFT_SAVE(Any p0) { invoke<Void>(0x1A3BAC68, p0); }// 0x1A3BAC68
   static void _0xED40F27D(Any p0) { invoke<Void>(0xED40F27D); } // 0xED40F27D //Auto Save?
   static int _0x8C710D3E() { return invoke<int>(0x8C710D3E); } // 0x8C710D3E
   static int _0x17F34613(int p0) { return invoke<int>(0x17F34613, p0); } // 0x17F34613
   static int _0x20CE8AA8(int p0, int p1, unsigned int p2, int p3, int p4) { return invoke<int>(0x20CE8AA8, p0, p1, p2, p3, p4); } // 0x20CE8AA8
   static int _0x8E867DDD(int p0) { return invoke<int>(0x8E867DDD, p0); } // 0x8E867DDD
   static int _0x6E79F939(int p0, int p1) { return invoke<int>(0x6E79F939, p0, p1); } // 0x6E79F939
   static int _0x3E647734(int p0, int p1, int p2) { return invoke<int>(0x3E647734, p0, p1, p2); } // 0x3E647734
   static int _0xE8637D2B(int p0, int p1, int p2, int p3, int p4) { return invoke<int>(0xE8637D2B, p0, p1, p2, p3, p4); } // 0xE8637D2B
   static int _0x6D59A25F(int p0, int p1) { return invoke<int>(0x6D59A25F, p0, p1); } // 0x6D59A25F
   static int _0x1D177160() { return invoke<int>(0x1D177160); } // 0x1D177160
   static int _0x1ADA1769() { return invoke<int>(0x1ADA1769); } // 0x1ADA1769
   static BOOL DOES_FILE_EXIST(Any p0) { return invoke<BOOL>(0xAABE1330, p0); } // 0xAABE1330
   static void _0xD44F7102() { invoke<Void>(0xD44F7102); } // 0xD44F7102
   static BOOL IS_DEV_BUILD() { return invoke<BOOL>(0x6D9AA768); } // 0x6D9AA768
   static BOOL IS_PS3() { return invoke<BOOL>(0xA369B36F); }// 0xA369B36F
   static BOOL _0xB427CB25() { return invoke<BOOL>(0xB427CB25); } // 0xB427CB25
   static int _IS_CACHE_PRIMED() { return invoke<int>(0x4BA92498); } // 0x4BA92498
   static BOOL IS_PLAYER_SIGNED_IN(Player player) { return invoke<BOOL>(0xC3C0F1F2, player); } // 0xC3C0F1F2
   static int GET_LOCAL_PLAYER_NAME() { return invoke<int>(0xA183D927); } // 0xA183D927
   static int _0x8BD88B43() { return invoke<int>(0x8BD88B43); } // 0x8BD88B43
   static int _0x1C7C0F86(int p0, int p1, int p2) { return invoke<int>(0x1C7C0F86, p0, p1, p2); } // 0x1C7C0F86
   static int _0x836F42DA(int p0, int p1, int p2, int p3) { return invoke<int>(0x836F42DA, p0, p1, p2, p3); }
   static void PAUSE_GAME(Any p0) { invoke<Void>(0x6F32A4E2, p0); } // 0x6F32A4E2
   static void UNPAUSE_GAME() { invoke<Void>(0x0BF2CD82); } // 0x0BF2CD82
   static BOOL IS_GAME_PAUSED() { return invoke<BOOL>(0x57246C02); } // 0x57246C02
   static int _0xF0DDF83D(Any p0) { return invoke<int>(0xF0DDF83D, p0); } // 0xF0DDF83D
   static void SET_MISSION_INFO(Any p0, Any p1) { invoke<Void>(0x3B417D4E, p0, p1); } // 0x3B417D4E
   static void CLEAR_MISSION_INFO() { invoke<Void>(0x02092A6E); } // 0x02092A6E
   static int _0x6CD7DCE1(float* p0, float* p1) { return invoke<int>(0x6CD7DCE1, p0, p1); } // 0x6CD7DCE1
   static void SET_START_POS(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x0CB93120, p0, p1, p2, p3, p4); } // 0x0CB93120
   static BOOL _0x814D97E8() { return invoke<BOOL>(0x814D97E8); } // 0x814D97E8
   static BOOL _0x3B004817() { return invoke<BOOL>(0x3B004817); } // 0x3B004817
   static void SCRIPT_DONE_LOADING() { invoke<Void>(0x5401F0CA); } // 0x5401F0CA
   static int LAUNCH_NEW_SCRIPT(const char* p0, Any p1) { return invoke<int>(0x85A30503, p0, p1); } // 0x85A30503
   static int _0xA602F586(Any* p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0xA602F586, p0, p1, p2, p3, p4); } // 0xA602F586
   static BOOL _0x7CE2C2E1() { return invoke<BOOL>(0x7CE2C2E1); } // 0x7CE2C2E1
   static BOOL _0xD8E31D42() { return invoke<BOOL>(0xD8E31D42); } // 0xD8E31D42
   static BOOL _0x9A73C2CD() { return invoke<BOOL>(0x9A73C2CD); } // 0x9A73C2CD
   static BOOL IS_DISPLAY_WIDESCREEN() { return invoke<BOOL>(0x554FC5E0); } // 0x554FC5E0
   static int _0x6226328F() { return invoke<int>(0x6226328F); } // 0x6226328F
   static int _0x59F98CA9(Any p0) { return invoke<int>(0x59F98CA9, p0); } // 0x59F98CA9
   static int GET_GAME_EDITION() { return invoke<int>(0xB5401D4A); } // 0xB5401D4A
}

namespace GAMERTAG
{
   static int _0xF62EE158() { return invoke<int>(0xF62EE158); } // 0xF62EE158
   static void _0x449D4A89(Any p0) { invoke<Void>(0x449D4A89, p0); } // 0x449D4A89
   static int _0xAEC955F8(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0xAEC955F8, p0, p1, p2, p3, p4, p5); } // 0xAEC955F8
   static int _0x211DE185(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return invoke<int>(0x211DE185, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x211DE185
   static Any CREATE_MP_TEXT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x5BF5A39C, p0, p1, p2, p3, p4, p5); } // 0x5BF5A39C
}

namespace GATEWAY
{
   static Any GATEWAY_GET_ACTOR(Any p0) { return invoke<Any>(0x820699A8, p0); } // 0x820699A8
   static Any GATEWAY_SET_ACTOR(Any p0) { return invoke<Any>(0x26D24123, p0); } // 0x26D24123
   static Any GATEWAY_GET_VOLUME(Any p0) { return invoke<Any>(0x987AD426, p0); } // 0x987AD426
   static Any GATEWAY_GET_MARKER(Any p0) { return invoke<Any>(0xB62A4FB1, p0); } // 0xB62A4FB1
   static Any GATEWAY_UPDATE(Any p0) { return invoke<Any>(0x96BD89B6, p0); } // 0x96BD89B6
   static Any ACTOR_DATA_GRAVITY_LIMIT(Any p0) { return invoke<Any>(0xF03CC7A7, p0); } // 0xF03CC7A7
   static Any GATEWAY_DISABLE() { return invoke<Any>(0x620A3C17); } // 0x620A3C17
   static Any _0x3AE1062C() { return invoke<Any>(0x3AE1062C); } // 0x3AE1062C
   static Any GATEWAY_IS_DISABLED(Any p0) { return invoke<Any>(0xB9F2F8BB, p0); } // 0xB9F2F8BB
}

namespace GOHEVENT
{
   static int _AIATTENTIONATTRACTOR(Any p0, Any p1, float p2, float p3, float p4, float p5, float p6) { return invoke<int>(0x945F518F, p0, p1, p2, p3, p4, p5, p6); } // 0x945F518F
}

namespace GRINGO
{
   static BOOL IS_GRINGO_ACTIVE() { return invoke<BOOL>(0x86F2C24D); } // 0x86F2C24D
   static BOOL IS_GRINGO_READY(Any p0) { return invoke<BOOL>(0xB9BFCB41, p0); } // 0xB9BFCB41
   static BOOL GRINGO_IS_ACTIVE(Any p0) { return invoke<BOOL>(0xB8A48688, p0); } // 0xB8A48688
   static int GRINGO_GET_TARGET(Any p0) { return invoke<int>(0xC70FDA39, p0); } // 0xC70FDA39
   static void GRINGO_WAIT(Any p0) { invoke<Void>(0x738FA66B, p0); } // 0x738FA66B
   static int GRINGO_FORCE_UPDATE(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x4B29AED2, p0, p1, p2, p3); } // 0x4B29AED2
   static void GRINGO_STOP() { invoke<Void>(0x59647303); } // 0x59647303
   static int GRINGO_STAY_ACTIVE(Any p0, Any p1) { return invoke<int>(0x9175FCFA, p0, p1); } // 0x9175FCFA
   static int GRINGO_DEACTIVATE(Any p0) { return invoke<int>(0x25636669, p0); } // 0x25636669
   static int _DEACTIVATE_GRINGO(Any p0) { return invoke<int>(0xA9F5CDCB, p0); } // 0xA9F5CDCB
   static void GRINGO_ENABLE_TYPE(Any p0) { invoke<Void>(0xCB58D301, p0); } // 0xCB58D301
   static void GRINGO_DISABLE_TYPE(Any p0) { invoke<Void>(0xCB91CC6E, p0); } // 0xCB91CC6E
   static int GRINGO_ENABLE_SPAWN(Any p0, Any p1) { return invoke<int>(0xA5EDCA4A, p0, p1); } // 0xA5EDCA4A
   static int _0xB1FCFFDC(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xB1FCFFDC, p0, p1, p2, p3); } // 0xB1FCFFDC
   static int _0x99356925(Any p0, Any p1, Any p2) { return invoke<int>(0x99356925, p0, p1, p2); } // 0x99356925
   static int _0xBD269877(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0xBD269877, p0, p1, p2, p3, p4); } // 0xBD269877
   static int _0x08D76BB0(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x08D76BB0, p0, p1, p2, p3); } // 0x08D76BB0
   static int _0xE9612679(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0xE9612679, p0, p1, p2, p3, p4); } // 0xE9612679
   static int _0xFA37C0FA(Any p0, Any p1, Any p2) { return invoke<int>(0xFA37C0FA, p0, p1, p2); } // 0xFA37C0FA
   static int _0x38771B89(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return invoke<int>(0x38771B89, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0x38771B89
   static int _0xC426D16F(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { return invoke<int>(0xC426D16F, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0xC426D16F
   static int _0xF8F80679(Any p0, Any p1, Any p2) { return invoke<int>(0xF8F80679, p0, p1, p2); } // 0xF8F80679
   static void GRINGO_LOAD_ANIMATION(Any p0) { invoke<Void>(0x78B655B1, p0); } // 0x78B655B1
   static void GRINGO_UNLOAD_ANIMATION(Any p0) { invoke<Void>(0x777842E3, p0); }// 0x777842E3
   static int _0x7D600F2F(Any p0, Any p1, Any p2) { return invoke<int>(0x7D600F2F, p0, p1, p2); } // 0x7D600F2F
   static int _0xBEF32D17(Any p0, Any p1, Any p2) { return invoke<int>(0xBEF32D17, p0, p1, p2); } // 0xBEF32D17
   static int _0x2C57A529(Any p0, Any p1, Any p2) { return invoke<int>(0x2C57A529, p0, p1, p2); } // 0x2C57A529
   static int _0x8EB5CE58(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x8EB5CE58, p0, p1, p2, p3); } // 0x8EB5CE58
   static int _0x7A759A53(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x7A759A53, p0, p1, p2, p3); } // 0x7A759A53
   static BOOL _0x0DC149BD(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x0DC149BD, p0, p1, p2, p3); }  // 0x0DC149BD
   static void GRINGO_ENABLE_PLAYER_CONTROL(Any p0, Any p1) { invoke<Void>(0x0B853FD5, p0, p1); } // 0x0B853FD5
   static int _GET_USE_COMPONENT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0xF8D9688A, p0, p1, p2, p3, p4, p5); } // 0xF8D9688A
   static void _GET_USE_COMPONENT_2(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x80317230, p0, p1, p2, p3, p4); } // 0x80317230
   static int _0xE2DCFF34(Any p0, Any p1, Any p2) { return invoke<int>(0xE2DCFF34, p0, p1, p2); } // 0xE2DCFF34
   static int _0xF4015EFC(Any p0) { return invoke<int>(0xF4015EFC, p0); } // 0xF4015EFC
   static int _0x0A0E660E() { return invoke<int>(0x0A0E660E); } // 0x0A0E660E
   static int _0x5F7176D6() { return invoke<int>(0x5F7176D6); } // 0x5F7176D6
   static int _0xAE7B3880() { return invoke<int>(0xAE7B3880); } // 0xAE7B3880
   static int _0xBBB2780E() { return invoke<int>(0xBBB2780E); } // 0xBBB2780E
   static void _SET_OWNERSHIP(Any p0, Any p1) { invoke<Void>(0x761BA4BD, p0, p1); } // 0x761BA4BD
   static void _SET_USE_CASE_OWNER(Any p0, Any p1, Any p2) { invoke<Void>(0x6E86FCB5, p0, p1, p2); } // 0x6E86FCB5
   static void _SET_CHILD_ACTIVATIONS(Any p0, Any p1) { invoke<Void>(0x89DE8A75, p0, p1); } // 0x89DE8A75
   static void _SET_COMMON_LAYER_ACTIVATIONS(Any p0, Any p1) { invoke<Void>(0x53B9569C, p0, p1); } // 0x53B9569C
   static int GRINGO_HANDLES_MOVEMENT(Any p0) { return invoke<int>(0xEDF3BF37, p0); } // 0xEDF3BF37
   static BOOL IS_GRINGO_COMPONENT_VALID(Any p0) { return invoke<BOOL>(0xBD503DC2, p0); } // 0xBD503DC2
   static int _COMPONENT_OF_NAME(Any p0, Any p1) { return invoke<int>(0xA766EA5C, p0, p1); } // 0xA766EA5C
   static int GRINGO_GET_COMPONENT_HASH(Any p0) { return invoke<int>(0x14E53D6F, p0); } // 0x14E53D6F
   static int _IS_COMPONENT_OF_TYPE(Any p0, Any p1) { return invoke<int>(0x284DD17C, p0, p1); } // 0x284DD17C
   static int _0xE4C686BA(Any p0, Any p1, Any p2) { return invoke<int>(0xE4C686BA, p0, p1, p2); } // 0xE4C686BA
   static int _0x3E8F94BE(Any p0, Any p1) { return invoke<int>(0x3E8F94BE, p0, p1); } // 0x3E8F94BE
   static int _GET_INDEX_OF_NAMED_TYPED_CHILD_COMPONENT_FUNC(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xDD807723, p0, p1, p2, p3); } // 0xDD807723
   static int _0xD6EE9534(Any p0, Any p1, Any p2) { return invoke<int>(0xD6EE9534, p0, p1, p2); } // 0xD6EE9534
   static int _GET_CHILD_COMPONENT_COUNT(Any p0) { return invoke<int>(0x3FA5FC03, p0); } // 0x3FA5FC03
   static int _0xAD313D88(Any p0, Any p1) { return invoke<int>(0xAD313D88, p0, p1); } // 0xAD313D88
   static int _0xA20141C0(Any p0) { return invoke<int>(0xA20141C0, p0); } // 0xA20141C0
   static int _0x9AD6D5B1(Any p0, Any p1) { return invoke<int>(0x9AD6D5B1, p0, p1); } // 0x9AD6D5B1
   static int _GET_PARENT_COMPONENT(Any p0, Any p1) { return invoke<int>(0xD282013F, p0, p1); } // 0xD282013F
   static int _GET_USE_COMPONENT_POSITION(Any p0, Any p1, Any p2) { return invoke<int>(0xBC32DA9A, p0, p1, p2); } // 0xBC32DA9A
   static void GRINGO_SET_MESSAGE_RETURN(Any p0) { invoke<Void>(0x37D0F3E9, p0); } // 0x37D0F3E9
   static int _0xCA589BAB() { return invoke<int>(0xCA589BAB); } // 0xCA589BAB
   static int _0xF550F8E7() { return invoke<int>(0xF550F8E7); } // 0xF550F8E7
   static int _0x54745DB0() { return invoke<int>(0x54745DB0); } // 0x54745DB0
   static int _0x2F096285() { return invoke<int>(0x2F096285); } // 0x2F096285
   static void GRINGO_SET_REQUEST_STRING(Any p0) { invoke<Void>(0x7F3020EB, p0); } // 0x7F3020EB
   static void _0x8CAF5C5C(Any p0) { invoke<Void>(0x8CAF5C5C, p0); } // 0x8CAF5C5C
   static int _0x926FD361() { return invoke<int>(0x926FD361); } // 0x926FD361
   static int _0x3DEA631B(Any p0, Any p1) { return invoke<int>(0x3DEA631B, p0, p1); } // 0x3DEA631B
   static int _0x5CFBF505(Any p0) { return invoke<int>(0x5CFBF505, p0); } // 0x5CFBF505
   static int _0x3A31175A(Any p0) { return invoke<int>(0x3A31175A, p0); } // 0x3A31175A
   static int _0x405E3903(Any p0, Any p1, Any p2) { return invoke<int>(0x405E3903, p0, p1, p2); } // 0x405E3903
   static int _0xCE210220(Any p0, Any p1, Any p2) { return invoke<int>(0xCE210220, p0, p1, p2); } // 0xCE210220
   static int _0xA9E00433(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0xA9E00433, p0, p1, p2, p3, p4, p5); } // 0xA9E00433
   static int _0xECD4F604(Any p0, Any p1) { return invoke<int>(0xECD4F604, p0, p1); } // 0xECD4F604
   static int _0x5AF74E19(Any p0, Any p1) { return invoke<int>(0x5AF74E19, p0, p1); } // 0x5AF74E19
   static int _0x51581898(Any p0) { return invoke<int>(0x51581898, p0); } // 0x51581898
   static int _0xD62D413C(Any p0) { return invoke<int>(0xD62D413C, p0); } // 0xD62D413C
   static int _0x92FE8D74(Any p0, Any p1) { return invoke<int>(0x92FE8D74, p0, p1); } // 0x92FE8D74
   static int _0x8C2914C4(Any p0, Any p1) { return invoke<int>(0x8C2914C4, p0, p1); } // 0x8C2914C4
   static int _0x5B46757F(Any p0) { return invoke<int>(0x5B46757F, p0); } // 0x5B46757F
   static int _0xD14515A3(Any p0, Any p1) { return invoke<int>(0xD14515A3, p0, p1); } // 0xD14515A3
   static int _0xF95DDBF2(Any p0, Any p1) { return invoke<int>(0xF95DDBF2, p0, p1); } // 0xF95DDBF2
   static int _0x6ADC74CE(Any p0, Any p1) { return invoke<int>(0x6ADC74CE, p0, p1); } // 0x6ADC74CE
   static int _0xB78BC233(Any p0, Any p1, Any p2) { return invoke<int>(0xB78BC233, p0, p1, p2); } // 0xB78BC233
   static int _0x5388F37D() { return invoke<int>(0x5388F37D); } // 0x5388F37D
   static void GRINGO_SET_COMPONENT_USER(Any p0, Any p1) { invoke<Void>(0x94F442D0, p0, p1); } // 0x94F442D0
   static int _0x15A0E28B(Any p0) { return invoke<int>(0x15A0E28B, p0); } // 0x15A0E28B
   static void _0x90FBBB8B(Any p0) { invoke<Void>(0x90FBBB8B, p0); } // 0x90FBBB8B
   static int _0x0208A8E0(Any p0, Any p1) { return invoke<int>(0x0208A8E0, p0, p1); } // 0x0208A8E0 
   static int _0x217B4264(Any p0, Any p1, Any p2) { return invoke<int>(0x217B4264, p0, p1, p2); } // 0x217B4264
   static int _0x5C11B011(Any p0, Any p1) { return invoke<int>(0x5C11B011, p0, p1); } // 0x5C11B011
   static int _0x5F516FC3(Any p0) { return invoke<int>(0x5F516FC3, p0); } // 0x5F516FC3
   static void _0xB62FE25C(Any p0, Any p1) { invoke<Void>(0xB62FE25C, p0, p1); } // 0xB62FE25C
   static int _0xE18BCD70(Any p0, Any p1, Any p2) { return invoke<int>(0xE18BCD70, p0, p1, p2); } // 0xE18BCD70
   static int _0x35279C3F(Any p0, Any p1) { return invoke<int>(0x35279C3F, p0, p1); } // 0x35279C3F
   static int GRINGO_RETURN_ACTOR_TO_DEFAULT_ANIMS(Any p0) { return invoke<int>(0xB62D549E, p0); } // 0xB62D549E
   static int _0xE9C74577(Any p0) { return invoke<int>(0xE9C74577, p0); } // 0xE9C74577
   static int _0xB8C419C3(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0xB8C419C3, p0, p1, p2, p3, p4, p5); } // 0xB8C419C3
   static void _0x0B9AE52F(Any p0) { invoke<Void>(0x0B9AE52F, p0); } // 0x0B9AE52F
   static int ATTACH_PROP_TO_ANIM(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0x0436C0BF, p0, p1, p2, p3, p4, p5); } // 0x0436C0BF
   static int _0x4DB7C61C(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x4DB7C61C, p0, p1, p2, p3, p4); } // 0x4DB7C61C
   static int _0xB96874B4(Any p0) { return invoke<int>(0xB96874B4, p0); } // 0xB96874B4
   static int ATTACH_SLOT_FROM_STRING(Any p0) { return invoke<int>(0x4A61BD63); } // 0x4A61BD63
   static int _0xADBF3ADF(Any p0) { return invoke<int>(0xADBF3ADF, p0); } // 0xADBF3ADF
   static int _0x721FC9A4(Any p0) { return invoke<int>(0x721FC9A4, p0); }  // 0x721FC9A4
   static int _0x87BA5FE9(Any p0, Any p1) { return invoke<int>(0x87BA5FE9, p0, p1); } // 0x87BA5FE9
   static int _GET_ANIM_ACT_ROOT_NODE(Any p0) { return invoke<int>(0x6263F909, p0); } // 0x6263F909
   static int _IS_SUBNODE_PLAYING_BY_HASH(Any p0, Any p1, Any p2) { return invoke<int>(0xB555A648, p0, p1, p2); } // 0xB555A648
   static int _PLAY_NODE_BY_HASH(Any p0, Any p1, Any p2) { return invoke<int>(0xAFD53217, p0, p1, p2); } // 0xAFD53217
   static int GRINGO_ACTOR_FACE(Any p0, Any p1, Any p2) { return invoke<int>(0x29C63CE6, p0, p1, p2); } // 0x29C63CE6
   static int GRINGO_ACTOR_MOVE_TO(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x698105FC, p0, p1, p2, p3, p4); } // 0x698105FC
   static int GRINGO_ACTOR_MOVE_TO_AND_FACE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<int>(0x0AF4FCB9, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x0AF4FCB9
   static int _GRINGO_ACTOR_MOVE_TO_AND_FACE_2(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return invoke<int>(0xEEE9C799, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xEEE9C799
   static void GRINGO_SET_PROP_COLLISIONS(Any p0, Any p1) { invoke<Void>(0x98543454, p0, p1); } // 0x98543454
   static void _0x6BA667B5(Any p0) { invoke<Void>(0x6BA667B5, p0); } // 0x6BA667B5
   static int GRINGO_IS_PROP_READY(Any p0) { return invoke<int>(0x24BAABCA, p0); } // 0x24BAABCA
   static int GRINGO_GET_PHYSINST(Any p0) { return invoke<int>(0x5EC1CABF, p0); } // 0x5EC1CABF
   static void _PROP_RESET_GRACE_FULLY(Any p0) { invoke<Void>(0x22D573D2, p0); } // 0x22D573D2
   static int _0xFF1FC1EF() { return invoke<int>(0xFF1FC1EF); } // 0xFF1FC1EF
   static int GET_GRINGO_BOOL_ATTR(Any p0, Any p1, Any p2) { return invoke<int>(0xFACF08C7, p0, p1, p2); } // 0xFACF08C7
   static int GET_GRINGO_INT_ATTR(Any p0, Any p1, Any p2) { return invoke<int>(0x8A86AF8B, p0, p1, p2); } // 0x8A86AF8B
   static int _0x869D5D92(Any p0, Any p1, Any p2) { return invoke<int>(0x869D5D92, p0, p1, p2); } // 0x869D5D92
   static int GET_GRINGO_STRUCT_ATTR(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xFA22A365, p0, p1, p2, p3); } // 0xFA22A365
   static int GET_GRINGO_FLOAT_ATTR(Any p0, Any p1, Any p2) { return invoke<int>(0x2EFD2B55, p0, p1, p2); } // 0x2EFD2B55
   static int GET_GRINGO_VECTOR_ATTR(Any p0, Any p1, Any p2) { return invoke<int>(0x5851C408, p0, p1, p2); } // 0x5851C408
   static int _0x1F74EE6C(Any p0, Any p1, Any p2) { return invoke<int>(0x1F74EE6C, p0, p1, p2); }  // 0x1F74EE6C
   static int _0x7E4681E8(Any p0, Any p1, Any p2) { return invoke<int>(0x7E4681E8, p0, p1, p2); } // 0x7E4681E8
   static int GET_GRINGO_STRING_ATTR(Any p0, Any p1, Any p2) { return invoke<int>(0x6BA58AC7, p0, p1, p2); } // 0x6BA58AC7
   static int SET_GRINGO_BOOL_ATTR(Any p0, Any p1, Any p2) { return invoke<int>(0xCF6822D7, p0, p1, p2); } // 0xCF6822D7
   static int SET_GRINGO_INT_ATTR(Any p0, Any p1, Any p2) { return invoke<int>(0x377B2C54, p0, p1, p2); } // 0x377B2C54
   static int _0xAFF7D382(Any p0, Any p1, Any p2) { return invoke<int>(0xAFF7D382, p0, p1, p2); } // 0xAFF7D382
   static int SET_GRINGO_FLOAT_ATTR(Any p0, Any p1, Any p2) { return invoke<int>(0xBC3C401F, p0, p1, p2); } // 0xBC3C401F
   static int SET_GRINGO_VECTOR_ATTR(Any p0, Any p1, Any p2) { return invoke<int>(0x5C6831F9, p0, p1, p2); } // 0x5C6831F9
   static int GRINGO_QUERY_BOOL(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x5C2174C7, p0, p1, p2, p3); } // 0x5C2174C7
   static int GRINGO_QUERY_INT(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x6B1F2FEB, p0, p1, p2, p3); } // 0x6B1F2FEB
   static int _0x15D6F3C7(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x15D6F3C7, p0, p1, p2, p3); } // 0x15D6F3C7
   static int GRINGO_QUERY_STRUCT(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x1528F08B, p0, p1, p2, p3, p4); } // 0x1528F08B
   static int GRINGO_QUERY_FLOAT(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x69CF9B75, p0, p1, p2, p3); } // 0x69CF9B75
   static int GRINGO_QUERY_STRING(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x30AF0FA8, p0, p1, p2, p3); } // 0x30AF0FA8
   static int GRINGO_QUERY_PROP(Any p0, Any p1) { return invoke<int>(0x2A7B1EFE, p0, p1); } // 0x2A7B1EFE
   static int GRINGO_UPDATE_BOOL(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x554330CA, p0, p1, p2, p3); } // 0x554330CA
   static Any GRINGO_UPDATE_INT(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x0744FEE8, p0, p1, p2, p3); } // 0x0744FEE8
   static int _0x4685D538(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x4685D538, p0, p1, p2, p3); } // 0x4685D538
   static int GRINGO_UPDATE_STRUCT(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x4DE50AD9, p0, p1, p2, p3, p4); } // 0x4DE50AD9
   static int GRINGO_GET_ATTRIBUTE_COUNT(Any p0) { return invoke<int>(0x39B7D772, p0); } // 0x39B7D772
   static int GRINGO_GET_ATTRIBUTE(Any p0, Any p1) { return invoke<int>(0x19411B1F, p0, p1); } // 0x19411B1F
   static int _0xBED45A9A(Any p0) { return invoke<int>(0xBED45A9A, p0); } // 0xBED45A9A
   static int GRINGO_GET_ATTRIBUTE_HASH(Any p0) { return invoke<int>(0xD2680017, p0); } // 0xD2680017
   static int _0xF0991C9F(Any p0, Any p1) { return invoke<int>(0xF0991C9F, p0, p1); } // 0xF0991C9F
   static int _0xD7BB1792(Any p0, Any p1) { return invoke<int>(0xD7BB1792, p0, p1); } // 0xD7BB1792 //NO_STRING
   static int _0xF573B7DE(Any p0, Any p1) { return invoke<int>(0xF573B7DE, p0, p1); } // 0xF573B7DE
   static int _GET_ATTRIBUTE_TYPE_BY_HANDLE(Any p0) { return invoke<int>(0xBF322F5C, p0); } // 0xBF322F5C
}

namespace GUI
{
   static int GUI_MAKE_WINDOW(GUIWindow parent, Any p1, const char* windowName, const char* p3) { return invoke<int>(0xA20246AB, parent, p1, windowName, p3); } // 0xA20246AB
   static int GUI_MAKE_TEXT(int guiHandle, float x, float y, float z, const char* menuTitle, const char* gxtText, float p4) { return invoke<int>(0x68FC1001, guiHandle, x, y, z, menuTitle, gxtText, p4); } // 0x68FC1001
   static int GUI_MAKE_OVERLAY(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0xA2A68BAD, p0, p1, p2, p3, p4, p5); } // 0xA2A68BAD
   static GUIWindow _GUI_GET_WINDOW(int guiHandle, const char* windowName) { return invoke<GUIWindow>(0xF6207DF5, guiHandle, windowName); } // 0xF6207DF5
   static int _0xA7FF2899(Any p0, Any p1, Any p2) { return invoke<int>(0xA7FF2899, p0, p1, p2); } // 0xA7FF2899
   static int GUI_CLOSE_WINDOW(Any p0) { return invoke<int>(0xFDED9B11, p0); } // 0xFDED9B11
   static int GUI_WINDOW_VALID(GUIWindow p0) { return invoke<int>(0xA2E6FECB, p0); }
   static int GUI_SET_TEXT(int textHandle, const char* menuName) { return invoke<int>(0x5F3A1C35, textHandle, menuName); } // 0x5F3A1C35
   static int GUI_SET_TEXT_JUSTIFY(int textHandle, int JustifyType) { return invoke<int>(0x9CC6F183, textHandle, JustifyType); } // 0x9CC6F183
   static int GUI_SET_TEXT_COLOR(int textHandle, float R, float G, float B, float A) { return invoke<int>(0x7600ED4B, textHandle, R, G, B, A); } // 0x7600ED4B
   static GUIWindow GUI_MAIN_WINDOW() { return invoke<GUIWindow>(0x5405B8AA); } // 0x5405B8AA
   static int _0xB498108A() { return invoke<int>(0xB498108A); } // 0xB498108A
   static int _0xC7DEB717() { return invoke<int>(0xC7DEB717); } // 0xC7DEB717
   static int _0xD019FF37(Any p0) { return invoke<int>(0xD019FF37, p0); } // 0xD019FF37
   static int _0x4803C120(float p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<int>(0x4803C120, p0, p1, p2, p4, p5, p6); } // 0x4803C120
   static int _CREATE_FONT(Any p0, Any p1, Any p2) { return invoke<int>(0xFA6BDD8E, p0, p1, p2); } // 0xFA6BDD8E
   static const char* _0x47EF426D(const char* p0) { return invoke<const char*>(0x47EF426D, p0); } // 0x47EF426D
   static int _0x52C10147(Any p0) { return invoke<int>(0x52C10147, p0); } // 0x52C10147
   static int _0x5E339E16(Any p0) { return invoke<int>(0x5E339E16, p0); } // 0x5E339E16
   static const char* _FLOAT_TO_STRING(float value, Any p1, int precision) { return invoke<const char*>(0x8ED1FF95, value, p1, precision); } // 0x8ED1FF95
   static const char* INT_TO_STRING(Any p0) { return invoke<const char*>(0xA883AFCC, p0); } // 0xA883AFCC
   static const char* VECTOR_TO_STRING(Vector3* p0) { return invoke<const char*>(0x6B8E4CDD, p0); } // 0x6B8E4CDD
}

namespace HOLSTER
{
   static Any ACTOR_HOLSTER_WEAPON(Any p0, Any p1) { return invoke<Any>(0xFE9903CC, p0, p1); } // FE9903CC
   static int _0x7957CA4F(Any p0, Any p1, Any p2) { return invoke<int>(0x7957CA4F, p0, p1, p2); } // 0x7957CA4F
   static int _END_FORCE_HOLSTER(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x231E7034, p0, p1, p2, p3, p4); } // 0x231E7034
   static int _DRAW_LAST_WEAPON(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x8FFDCE5C, p0, p1, p2, p3, p4); } // 0x8FFDCE5C
   static int ACTOR_DRAW_ANY_WEAPON(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0xD86BFBD8, p0, p1, p2, p3, p4); } // 0xD86BFBD8
   static void ACTOR_DRAW_WEAPON(Any p0, Any p1, Any p2) { invoke<Void>(0x953FB7EE, p0, p1, p2); } // 0x953FB7EE
   static int _IS_HOLSTERED(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x6426CCD6, p0, p1, p2, p3, p4); } // 0x6426CCD6
   static int _0x2E84E682(Any p0, Any p1) { return invoke<int>(0x2E84E682, p0, p1); } // 0x2E84E682
   static int _0x261A4C0E(Any p0, Any p1, float p2) { return invoke<int>(0x261A4C0E, p0, p1, p2); } // 0x261A4C0E
   static int _0x79EFDF7E(float p0) { return invoke<int>(0x79EFDF7E, p0); } // 0x79EFDF7E
   static int _0x5D863C30(Any p0, Any p1, float p2) { return invoke<int>(0x5D863C30, p0, p1, p2); } // 0x5D863C30
   static int _0xF71A883A(Any p0, Any p1, float p2) { return invoke<int>(0xF71A883A, p0, p1, p2); } // 0xF71A883A
   static int _0xCA669478(Any p0, float p1) { return invoke<int>(0xCA669478, p0, p1); } // 0xCA669478
   static int _0x7DA34015(Any p0, Any p1) { return invoke<int>(0x7DA34015, p0, p1); } // 0x7DA34015
}

namespace HUD
{
   static void UI_SET_PROMPT_STRING(Any p0, Any p1) { invoke<Void>(0xFA0CF208, p0, p1); } // 0xFA0CF208
   static void UI_SET_PROMPT_ICON(Any p0, Any p1) { invoke<Void>(0xA77E0DDF, p0, p1); } // 0xA77E0DDF
   static void UI_HIDE_PROMPT(Any p0) { invoke<Void>(0x545EC471, p0); } // 0x545EC471
   static int FLASH_SET_BOOL(Any p0, Any p1, const char* p2) { return invoke<int>(0x34F03EC7, p0, p1, p2); } // 0x34F03EC7
   static int FLASH_SET_INT(const char* scaleformName, const char* scaleformVarName, int value) { return invoke<int>(0x4778A580, scaleformName, scaleformVarName, value); } // 0x4778A580
   static int FLASH_SET_FLOAT(Any p0, Any p1, float p2) { return invoke<float>(0xDF024C94, p0, p1, p2); } // 0xDF024C94
   static int _0x8A2A1A51(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x8A2A1A51, p0, p1, p2, p3); } // 0x8A2A1A51
   static int FLASH_SET_STRING(const char* scaleformName, const char* scaleformVarName, Any p2, Any p3) { return invoke<int>(0x9E31EEA7, scaleformName, scaleformVarName, p2, p3); } // 0x9E31EEA7
   static int _0x35CDFDC5(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x35CDFDC5, p0, p1, p2, p3, p4); } // 0x35CDFDC5
   static int FLASH_GET_BOOL(Any p0, Any p1) { return invoke<int>(0xFA266B15, p0, p1); } // 0xFA266B15
   static int FLASH_GET_INT(const char* ScaleName, const char* ScaleVarName) { return invoke<int>(0x03568B83, ScaleName, ScaleVarName); } // 0x03568B83
   static float FLASH_GET_FLOAT(Any p0, Any p1) { return invoke<float>(0xA332ACE3, p0, p1); } // 0xA332ACE3
   static int _0xE39B92B7(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<int>(0xE39B92B7, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xE39B92B7
   static void PRINT_BIG(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x637016C9, p0, p1, p2, p3, p4); } // 0x637016C9
   static int _0x04A38C60(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any* p6) { return invoke<int>(0x04A38C60, p0, p1, p2, p3, p4, p5, p6); } // 0x04A38C60
   static void PRINT_HELP_B(const char* txt, float time, BOOL playSound, Any p3, Any p4, BOOL p5, const char* unk, const char* audioName) { invoke<Void>(0xE42A8278, txt, time, playSound, p3, p4, p5, unk, audioName); } // 0xE42A8278
   static void _PRINT_SUBTITLE(const char* txt, float time, BOOL isStringLiteral, int printType, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x32394BB6, txt, time, isStringLiteral, printType, p4, p5, p6, p7); } // 0x32394BB6
   static void PRINT_MONEY(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x51948EA6, p0, p1, p2, p3, p4, p5); } // 0x51948EA6
   static void PRINT_BIG_FORMAT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0xBCB8D17F, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xBCB8D17F
   static void PRINT_SMALL_FORMAT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0xBBBDFF7C, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xBBBDFF7C
   static void PRINT_OBJECTIVE_FORMAT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { invoke<Void>(0x283B4EFC, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0x283B4EFC
   static void PRINT_HELP_FORMAT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0xD8AAF8E0, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xD8AAF8E0
   static int _0x14708CB1() { return invoke<int>(0x14708CB1); } // 0x14708CB1
   static int _0xB9D95B4C() { return invoke<int>(0xB9D95B4C); } // 0xB9D95B4C
   static int _0x710B3A83() { return invoke<int>(0x710B3A83); } // 0x710B3A83
   static int _0x60135878() { return invoke<int>(0x60135878); } // 0x60135878
   static BOOL _0x2F0E7DE7() { return invoke<BOOL>(0x2F0E7DE7); } // 0x2F0E7DE7
   static BOOL _0x4B2FCAF6() { return invoke<BOOL>(0x4B2FCAF6); } // 0x4B2FCAF6
   static void HUD_CLEAR_SMALL_TEXT() { invoke<Void>(0x585F008A); } // 0x585F008A
   static void HUD_CLEAR_BIG_TEXT() { invoke<Void>(0xD6DFA6FC); } // 0xD6DFA6FC
   static void HUD_CLEAR_COUNTER() { invoke<Void>(0x050EFAAB); } // 0x050EFAAB
   static void HUD_CLEAR_OBJECTIVE() { invoke<Void>(0x160BDC7A); } // 0x160BDC7A
   static void HUD_CLEAR_HELP() { invoke<Void>(0x0095B908); } // 0x0095B908
   static int _0x02E1E708() { return invoke<int>(0x02E1E708); } // 0x02E1E708
   static int _0x777A1CA2() { return invoke<int>(0x777A1CA2); } // 0x777A1CA2
   static void HUD_CLEAR_OBJECTIVE_QUEUE() { invoke<Void>(0xE4DACF40); } // 0xE4DACF40
   static void HUD_CLEAR_HELP_QUEUE() { invoke<Void>(0x495164AD); } // 0x495164AD
   static const char* SET_RADAR_STREAMING(const char* p0) { return invoke<const char*>(0x0A07FE74, p0); } // 0x0A07FE74
   static int ADD_BLIP_FOR_ACTOR(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0xEFB9362F, p0, p1, p2, p3, p4); } // 0xEFB9362F
   static int ADD_BLIP_FOR_OBJECT(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x0E5372EC, p0, p1, p2, p3, p4); }// 0x0E5372EC
   static Any ADD_BLIP_FOR_COORD(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xC6F43D0E, p0, p1, p2, p3, p4); } // 0xC6F43D0E
   static int CHANGE_BLIP_ICON(Any p0, Any p1) { return invoke<int>(0xABD125F6, p0, p1); } // 0xABD125F6
   static int SET_BLIP_POS(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xB2EAF8DD, p0, p1, p2, p3); } // 0xB2EAF8DD
   static void SET_BLIP_SCALE(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x1E6EC434, p0, p1, p2, p3, p4); } // 0x1E6EC434
   static void SET_BLIP_COLOR(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xA2B8A736, p0, p1, p2, p3, p4); } // 0xA2B8A736
   static void SET_BLIP_PRIORITY(Any p0, Any p1) { invoke<Void>(0xCE87DA6F, p0, p1); }// 0xCE87DA6F
   static void SET_BLIP_BLINK(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x04B8C8C6, p0, p1, p2, p3); } // 0x04B8C8C6
   static void SET_BLIP_FLAG(Any p0, Any p1, Any p2) { invoke<Void>(0xA9A01C70, p0, p1, p2); } // 0xA9A01C70
   static void SET_BLIP_VISIBLE(Any p0, Any p1) { invoke<Void>(0x9318D3D2, p0, p1); } // 0x9318D3D2
   static Blip IS_BLIP_VISIBLE(Blip p0) { return invoke<Blip>(0x1E7A6623, p0); }// 0x1E7A6623
   static BOOL IS_BLIP_VALID(Any p0) { return invoke<BOOL>(0xDCC10BA9, p0); } // 0xDCC10BA9
   static void REMOVE_BLIP(Blip* blip) { invoke<Void>(0xD8C3C1CD, *blip); } // 0xD8C3C1CD
   static int _0x1449EE9E(Any p0) { return invoke<int>(0x1449EE9E, p0); } // 0x1449EE9E
   static Blip GET_BLIP_ON_OBJECT(Object p0) { return invoke<Blip>(0xE3E30992, p0); }// 0xE3E30992
   static int GET_BLIP_ICON(Any p0) { return invoke<int>(0xEE4F4B7D, p0); } // 0xEE4F4B7D
   static int SET_CURRENT_MAP(Any p0) { return invoke<int>(0x014C7C29, p0); } // 0x014C7C29
   static void SET_STAMINA_BLINK(Any p0) { invoke<Void>(0x39F2E5F1, p0); } // 0x39F2E5F1
   static void SET_DEADEYE_BLINK(Any p0) { invoke<Void>(0xA543B120, p0); } // 0xA543B120
   static void _0x7FF20D84(Any p0) { invoke<Void>(0x7FF20D84, p0); } // 0x7FF20D84
   static void _0x364450B1(Any p0) { invoke<Void>(0x364450B1, p0); }  // 0x364450B1
   static void _0xB4614D11(Any p0, Any p1) { invoke<Void>(0xB4614D11, p0, p1); } // 0xB4614D11
   static Any GET_RADAR_RADIUS() { return invoke<Any>(0x6B33CBCC); } // 0x6B33CBCC
   static void _0x33CE49C9() { invoke<Void>(0x33CE49C9); } // 0x33CE49C9
   static int _0x1D85FB58() { return invoke<int>(0x1D85FB58); } // 0x1D85FB58
   static void _0x2148AC15(Any p0, Any p1) { invoke<Void>(0x2148AC15, p0, p1); } // 0x2148AC15
   static void _0x444C3C32(Any p0, Any p1, Any p2) { invoke<Void>(0x444C3C32, p0, p1, p2); } // 0x444C3C32
   static void _0x1E98AFEC(Any p0, Any p1) { invoke<Void>(0x1E98AFEC, p0, p1); } // 0x1E98AFEC
   static void _0xFF3DB575(Any p0, Any p1) { invoke<Void>(0xFF3DB575, p0, p1); } // 0xFF3DB575
   static int _0xD76F1E9A(Any p0) { return invoke<int>(0xD76F1E9A, p0); } // 0xD76F1E9A
   static void SET_BLIP_IMPAIRMENT_MASK(Any p0, Any p1) { invoke<Void>(0xBC05EBB3, p0, p1); }// 0xBC05EBB3
   static void _0xCE79F8E2(Any p0, Any p1) { invoke<Void>(0xCE79F8E2, p0, p1); } // 0xCE79F8E2
   static void _0xFBA76D7E(Any p0, Any p1) { invoke<Void>(0xFBA76D7E, p0, p1); } // 0xFBA76D7E
   static void _0x6077F3AE(Any p0, Any p1) { invoke<Void>(0x6077F3AE, p0, p1); } // 0x6077F3AE
   static void SET_BLIP_NAME(Any p0, Any p1) { invoke<Void>(0xDC249B12, p0, p1); } // 0xDC249B12
   static void CLEAR_REGIONS() { invoke<Void>(0xB1DAEF0C); }  // 0xB1DAEF0C
   static int APPEND_REGION(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<int>(0x95666EE0, p0, p1, p2, p3, p4, p5, p6); } // 0x95666EE0
   static void _0x970AC1F7(Any p0, Any p1) { invoke<Void>(0x970AC1F7, p0, p1); } // 0x970AC1F7
   static int _0xF5B7B208() { return invoke<int>(0xF5B7B208); } // 0xF5B7B208
   static void _0xA094152A(Any p0) { invoke<Void>(0xA094152A, p0); } // 0xA094152A
   static void _0x0DFF578A(Any p0, Any p1, Any p2) { invoke<Void>(0x0DFF578A, p0, p1, p2); } // 0x0DFF578A
   static int IS_HUD_MAP_VISIBLE() { return invoke<int>(0xCE043618); } // 0xCE043618
   static void _0x48DB367D(Any p0) { invoke<Void>(0x48DB367D, p0); } // 0x48DB367D
   static void _0x4FCE7B9D(Any p0) { invoke<Void>(0x4FCE7B9D, p0); } // 0x4FCE7B9D
   static void _0x14585073(Any p0, Any p1) { invoke<Void>(0x14585073, p0, p1); } // 0x14585073
   static void _0x5EA2E02D(Any p0) { invoke<Void>(0x5EA2E02D, p0); } // 0x5EA2E02D
   static int _0xE78A0469(Any p0) { return invoke<int>(0xE78A0469, p0); } // 0xE78A0469
   static void _0x02755628(Any p0, Any p1) { invoke<Void>(0x02755628, p0, p1); } // 0x02755628
   static void SET_STAT_MESSAGE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12) { invoke<Void>(0x73DA6AF1, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 0x73DA6AF1
   static void CLEAR_STAT_MESSAGE() { invoke<Void>(0x906E0138); }  // 0x906E0138
   static int _0x919142BE() { return invoke<int>(0x919142BE); }// 0x919142BE
   static void HUD_TIMER_DISPLAY(Any p0) { invoke<Void>(0x149F9E46, p0); } // 0x149F9E46
   static int HUD_TIMER_GET() { return invoke<int>(0x1C6919EF); } // 0x1C6919EF
   static int HUD_TIMER_SET(float p0) { return invoke<int>(0xB6A24203, p0); } // 0xB6A24203
   static int _0x2395C147() { return invoke<int>(0x2395C147); } // 0x2395C147
   static void HUD_TIMER_COUNTDOWN(Any p0) { invoke<Void>(0xF4209CCC, p0); } // 0xF4209CCC
   static void HUD_TIMER_PAUSE() { invoke<Void>(0x3383E839); } // 0x3383E839
   static int HUD_TIMER_UNPAUSE() { return invoke<int>(0x983A7E4E); } // 0x983A7E4E
   static int _HUD_WANTED_METER(Any p0) { return invoke<int>(0x31A55281, p0); } // 0x31A55281
   static int _HUD_WANTED_CRIME(float p0) { return invoke<int>(0x651C1FC2, p0); } // 0x651C1FC2
   static void HUD_COUNTER_DISPLAY(Any p0) { invoke<Void>(0x9A35DFC6, p0); } // 0x9A35DFC6
   static void HUD_COUNTER_SET(Any p0) { invoke<Void>(0x7D94675D, p0); } // 0x7D94675D
   static void HUD_ENABLE(Any p0) { invoke<Void>(0x0C180A3F, p0); } // 0x0C180A3F
   static void HUD_SET_FADE_COLOR(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x4DA5F502, p0, p1, p2, p3); } // 0x4DA5F502
   static void HUD_FADE_OUT(Any p0, Any p1, Any p2) { invoke<Void>(0x52963366, p0, p1, p2); } // 0x52963366
   static void _0xB0B4296A() { invoke<Void>(0xB0B4296A); } // 0xB0B4296A
   static void HUD_FADE_IN(Any p0, Any p1) { invoke<Void>(0xF90F6C51, p0, p1); } // 0xF90F6C51
   static int _HUD_FADE_IN_EXECUTED(Any p0, Any p1, Any p2) { return invoke<int>(0x7E4A92CF, p0, p1, p2); } // 0x7E4A92CF
   static int HUD_IS_FADED() { return invoke<int>(0x4EFFFC06); } // 0x4EFFFC06
   static int HUD_IS_FADING() { return invoke<int>(0xE5CC6F08); } // 0xE5CC6F08
   static int _0xC6E36B1D(Any p0) { return invoke<int>(0xC6E36B1D, p0); } // 0xC6E36B1D
   static int _0xEF270DC9() { return invoke<int>(0xEF270DC9); } // 0xEF270DC9
   static void _0x18346D88() { invoke<Void>(0x18346D88); } // 0x18346D88
   static void _0xBB2EABF9(Any p0) { invoke<Void>(0xBB2EABF9, p0); } // 0xBB2EABF9
   static void _0x9E6D7105(Any p0) { invoke<Void>(0x9E6D7105, p0); } // 0x9E6D7105
   static int _0x82A290D4() { return invoke<int>(0x82A290D4); } // 0x82A290D4
   static int _0x0C197810() { return invoke<int>(0x0C197810); } // 0x0C197810
   static int _0xC64DF45D() { return invoke<int>(0xC64DF45D); } // 0xC64DF45D
   static void UI_TRANSITION_TO(Any p0) { invoke<Void>(0xD0F2D2B6, p0); } // 0xD0F2D2B6
   static int _0x111554E2(Any p0) { return invoke<int>(0x111554E2, p0); } // 0x111554E2
   static void UI_SEND_EVENT(Any p0) { invoke<Void>(0xB58825F5, p0); } // 0xB58825F5
   static void UI_ENTER(const char* uiLayer) { invoke<Void>(0x594F2657, uiLayer); } // 0x594F2657
   static void _0x4486E8C7() { invoke<Void>(0x4486E8C7); } // 0x4486E8C7
   static void _0x175CD937(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x175CD937, p0, p1, p2, p3); } // 0x175CD937
   static void _0x47D2DE08(Any p0, Any p1) { invoke<Void>(0x47D2DE08, p0, p1); } // 0x47D2DE08
   static void SET_GPS_PATH(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xD82F910C
   static int _0xAA322DFC(Any p0) { return invoke<int>(0xAA322DFC, p0); } // 0xAA322DFC
   static void CLEAR_GPS_PATH(Any p0) { invoke<Void>(0xD077D8B6, p0); } // 0xD077D8B6
   static int _0x82F63365(Any p0) { return invoke<int>(0x82F63365, p0); } // 0x82F63365
   static int _0x34711B59() { return invoke<int>(0x34711B59); } // 0x34711B59
   static int FIND_TRAFFIC_PATH(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0xA5BDC21D, p0, p1, p2, p3, p4, p5); } // 0xA5BDC21D
   static int _0x3E758743(Any p0) { return invoke<int>(0x3E758743, p0); } // 0x3E758743
   static int _0xB6E791F6(Any p0, Any p1) { return invoke<int>(0xB6E791F6, p0, p1); } // 0xB6E791F6
   static int _0xD12802AF(Any p0) { return invoke<int>(0xD12802AF, p0); } // 0xD12802AF
   static void HUD_STAMINA_OVERRIDE(Any p0, Any p1, Any p2) { invoke<Void>(0xADBD44F6, p0, p1, p2); } // 0xADBD44F6
   static int UI_CHEAT_GET_VALUE(Any p0) { return invoke<int>(0x94F5E63F, p0); } // 0x94F5E63F
   static void UI_CHEAT_SET_VALUE(Any p0, Any p1) { invoke<Void>(0x9E88643A, p0, p1); } // 0x9E88643A
   static int UI_CHEAT_GET_STATE(Any p0) { return invoke<int>(0x01309706, p0); } // 0x01309706
   static void UI_CHEAT_SET_STATE(Any p0, Any p1) { invoke<Void>(0x7D6A8D4A, p0, p1); } // 0x7D6A8D4A
   static void UI_CHEAT_SET_CODE(Any p0, Any p1) { invoke<Void>(0x90CD8795, p0, p1); } // 0x90CD8795
   static void UI_SET_HAS_CHEATED(Any p0) { invoke<Void>(0x7D0EFDD8, p0); } // 0x7D0EFDD8
   static int UI_HAS_CHEATED() { return invoke<int>(0xBAB151CB); } // 0xBAB151CB
   static void UI_DUMP_MESSAGE_QUEUE_TO_NOTES(Any p0) { invoke<Void>(0x714D6F72, p0); } // 0x714D6F72
   static void UI_CLEAR_MESSAGE_QUEUE(Any p0) { invoke<Void>(0x64DDB95D, p0); } // 0x64DDB95D
   static int _IS_MESSAGE_QUEUE_EMPTY(Any p0) { return invoke<int>(0x941FC468, p0); } // 0x941FC468
   static void UI_REMOVE_MESSAGE_IN_QUEUE(Any p0, Any p1, Any p2) { invoke<Void>(0x7725001B, p0, p1, p2); } // 0x7725001B
   static void _0xEB214384(Any p0) { invoke<Void>(0xEB214384, p0); } // 0xEB214384
   static int _0x6CC9CCE7() { return invoke<int>(0x6CC9CCE7); } // 0x6CC9CCE7
   static int _0x8701F1F6() { return invoke<int>(0x8701F1F6); } // 0x8701F1F6
   static int _0x3842B89F() { return invoke<int>(0x3842B89F); } // 0x3842B89F
   static int _0xFDB5FC03() { return invoke<int>(0xFDB5FC03); } // 0xFDB5FC03
}

namespace INDICATOR
{
   static void SET_INDICATOR_DRAW(Any p0, Any p1) { invoke<Void>(0x8E387228, p0, p1); } // 0x8E387228
}

namespace INTERSECTION
{
   static Any FIND_INTERSECTION(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<Any>(0x9CD3AD70, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x9CD3AD70
   static Any FIND_GROUND_INTERSECTION(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x6AD8EEAF, p0, p1, p2, p3); } // 0x6AD8EEAF
   static Any _0x77964B0C(Any p0) { return invoke<Any>(0x77964B0C, p0); } // 0x77964B0C
   static Any FIND_WATER_INTERSECTION(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<Any>(0x4F193BE4, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x4F193BE4
   static Any _0x5219B7D0(Any p0) { return invoke<Any>(0x5219B7D0, p0); } // 0x5219B7D0
   static Any GET_ACTOR_GROUND_MATERIAL(Any p0) { return invoke<Any>(0x451A8EF2, p0); } // 0x451A8EF2
   static Any _0x1E81DB60(Any p0) { return invoke<Any>(0x1E81DB60, p0); } // 0x1E81DB60
}

namespace JOURNAL
{
   static int SET_EXCLUSIVE_JOURNAL_ID(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x6398AF9A, p0, p1, p2, p3); } // 0x6398AF9A
   static int RESET_EXCLUSIVE_JOURNAL_ID(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x45E34464, p0, p1, p2, p3); } // 0x45E34464
   static int TOGGLE_COOP_JOURNAL_UI(int result, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x44A1ED5C, result, p1, p2, p3, p4); } // 0x44A1ED5C
   static int TOGGLE_JOURNAL_UI(int result, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0xE6726EF4, result, p1, p2, p3, p4, p5); } // 0xE6726EF4
   static int GET_JOURNAL_ENTRY(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xC450C870, p0, p1, p2, p3); } // 0xC450C870
   static int CREATE_JOURNAL_ENTRY(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x761FD935, p0, p1, p2, p3); } // 0x761FD935
   static int CREATE_JOURNAL_ENTRY_BY_HASH(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x619F1C3D, p0, p1, p2, p3); } // 0x619F1C3D
   static BOOL IS_JOURNAL_ENTRY_IN_LIST(Any p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0xC17FE40A, p0, p1, p2, p3); } // 0xC17FE40A
   static int GET_NUM_JOURNAL_ENTRIES_IN_LIST(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x3E84D766, p0, p1, p2, p3, p4); } // 0x3E84D766
   static int GET_JOURNAL_ENTRY_IN_LIST(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x49B02E18, p0, p1, p2, p3); } // 0x49B02E18
   static int PREPEND_JOURNAL_ENTRY(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x87DC7F5B, p0, p1, p2, p3); } // 0x87DC7F5B
   static int APPEND_JOURNAL_ENTRY(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x9C40CFAB, p0, p1, p2, p3); } // 0x9C40CFAB
   static int REMOVE_JOURNAL_ENTRY(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x01BF35BD, p0, p1, p2, p3); } // 0x01BF35BD
   static int CLEAR_JOURNAL_ENTRY(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xB8B7B818, p0, p1, p2, p3); } // 0xB8B7B818
   static int PREPEND_JOURNAL_ENTRY_DETAIL(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x81470AFE, p0, p1, p2, p3); } // 0x81470AFE
   static int APPEND_JOURNAL_ENTRY_DETAIL(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xF5DFD684, p0, p1, p2, p3); } // 0xF5DFD684
   static int CLEAR_JOURNAL_ENTRY_DETAIL_LIST(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xD0567D03, p0, p1, p2, p3); } // 0xD0567D03
   static int GET_JOURNAL_ENTRY_NUM_DETAILS(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xCF3A69FC, p0, p1, p2, p3); } // 0xCF3A69FC
   static int GET_JOURNAL_ENTRY_DETAIL_HASH_BY_INDEX(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x1630EFC5, p0, p1, p2, p3); } // 0x1630EFC5
   static int  GET_JOURNAL_ENTRY_DETAIL_STYLE_BY_HASH(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0xEBC9C2FD, p0, p1, p2, p3, p4); }// 0xEBC9C2FD
   static int SET_JOURNAL_ENTRY_DETAIL_STYLE(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x539D0404, p0, p1, p2, p3); }// 0x539D0404
   static int _SET_JOURNAL_ENTRY_DETAIL_STYLE2(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x5209C0C0, p0, p1, p2, p3); } // 0x5209C0C0
   static BOOL IS_JOURNAL_ENTRY_TARGETED(Any p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0xF0C4E96F, p0, p1, p2, p3); } // 0xF0C4E96F
   static int GET_JOURNAL_ENTRY_TYPE(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0xF6FEC269, p0, p1, p2, p3, p4); } // 0xF6FEC269
   static BOOL IS_JOURNAL_ENTRY_UPDATED(Any p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0x078F9B43, p0, p1, p2, p3); } // 0x078F9B43
   static int GET_JOURNAL_ENTRY_MISC_FLAG(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x8020011E, p0, p1, p2, p3); } // 0x8020011E
   static int GET_TARGETED_JOURNAL_ENTRY(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x8A9B8F0C, p0, p1, p2, p3); } // 0x8A9B8F0C
   static int TARGET_JOURNAL_ENTRY(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xC3DC9490, p0, p1, p2, p3); } // 0xC3DC9490
   static int SET_JOURNAL_ENTRY_UPDATED(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xCD4633BD, p0, p1, p2, p3); } // 0xCD4633BD
   static int SET_JOURNAL_ENTRY_TROPHY(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x5CB9D376, p0, p1, p2, p3); } // 0x5CB9D376
   static int DEACTIVATE_JOURNAL_ENTRY(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x196A1EDE, p0, p1, p2, p3); }// 0x196A1EDE
   static int SET_JOURNAL_ENTRY_PROGRESS(Any p0, Any p1, Any p2, Any p3, float p4) { return invoke<int>(0x5DC073DE, p0, p1, p2, p3, p4); } // 0x5DC073DE
   static float GET_JOURNAL_ENTRY_PROGRESS(Any p0, Any p1, Any p2, Any p3) { return invoke<float>(0xF2C1D690, p0, p1, p2, p3); } // 0xF2C1D690
   static int SET_JOURNAL_ENTRY_DISALLOW_TRACKING(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xF7687D41, p0, p1, p2, p3); } // 0xF7687D41
   static BOOL GET_JOURNAL_ENTRY_DISALLOW_TRACKING(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x93CA45DE, p0, p1, p2, p3); } // 0x93CA45DE
   static int SET_JOURNAL_ENTRY_CURRENT_OBJECTIVE(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x2AA8E2FA, p0, p1, p2, p3); } // 0x2AA8E2FA
   static int GET_LAST_NOTE_OBJECTIVE(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xDC28C12F, p0, p1, p2, p3); } // 0xDC28C12F
   static int APPEND_JOURNAL_NOTE(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x2B969E73, p0, p1, p2, p3); } // 0x2B969E73
}

namespace LASSO
{
   static Any GET_LASSO_TARGET(Any p0) { return invoke<Any>(0xAA364907, p0); } // 0xAA364907
   static Any GET_LASSO_USER(Any p0) { return invoke<Any>(0x3B775037, p0); } // 0x3B775037
   static Any GET_HOGTIED_MASTER(Any p0) { return invoke<Any>(0x1580F3BF, p0); } // 0x1580F3BF
   static Any _0xF68C926F(Any p0) { return invoke<Any>(0xF68C926F, p0); } // 0xF68C926F
   static void DETACH_LASSO(Any p0) { invoke<Void>(0x32030E7C, p0); } // 0x32030E7C
   static void FREE_FROM_HOGTIE(Any p0) { invoke<Void>(0x31AD57FE, p0); } // 0x31AD57FE
   static Any LASSO_EVENT(Any p0) { return invoke<Any>(0x98FAF5D7, p0); } // 0x98FAF5D7
   static Any _0xFF5F7D2C(Any p0) { return invoke<Any>(0xFF5F7D2C, p0); } // 0xFF5F7D2C
   static Any IS_ACTOR_BEING_DRAGGED(Any p0) { return invoke<Any>(0x5B792331, p0); } // 0x5B792331
   static BOOL IS_ACTOR_HOGTIED(Actor actor) { return invoke<BOOL>(0xA610DC79, actor); } // 0xA610DC79
   static BOOL IS_ACTOR_IN_HOGTIE(Any p0) { return invoke<BOOL>(0xB24ADC7C, p0); } // 0xB24ADC7C
   static Any GET_ACTOR_HOGTIE_STATE(Any p0) { return invoke<Any>(0xF45D9723, p0); } // 0xF45D9723
   static void HOGTIE_ACTOR(Any p0) { invoke<Void>(0x4440BCA5, p0); } // 0x4440BCA5
   static Any _0xCC04895F(Any p0) { return invoke<Any>(0xCC04895F, p0); } // 0xCC04895F
   static void SET_HOGTIE_ATTACH_VICTIM(Any p0, Any p1) { invoke<Void>(0xFA2B916E, p0, p1); } // 0xFA2B916E
   static void CLEAR_HOGTIE_ATTACH_VICTIM(Any p0, Any p1) { invoke<Void>(0xB7A802C2, p0, p1); } // 0xB7A802C2
   static Any IS_ACTOR_HOGTIE_ATTACHED(Any p0) { return invoke<Any>(0x16EB367C, p0); } // 0x16EB367C
   static Any _0xBCED635B(Any p0) { return invoke<Any>(0xBCED635B, p0); } // 0xBCED635B
   static Any _0x60D10483(Any p0) { return invoke<Any>(0x60D10483, p0); } // 0x60D10483
   static Any IS_HOGTIE_CUTFREE_OBSTRUCTED(Any p0) { return invoke<Any>(0x9377291F, p0); } // 0x9377291F
   static Any _0x9634D42E(Any p0) { return invoke<Any>(0x9634D42E, p0); } // 0x9634D42E
   static Any _0x8F8EDCCF(Any p0) { return invoke<Any>(0x8F8EDCCF, p0); } // 0x8F8EDCCF
}

namespace LAYOUT
{
   static Any _GET_NUM_SCRIPTS_ACTIVE(Hash p0) { return invoke<Any>(0x0B396DFF, p0); } // 0x0B396DFF
   static void _0x24F3A0DB(Any p0) { invoke<Void>(0x24F3A0DB, p0); } // 0x24F3A0DB
   static int  _0x26011C78(Any p0) { return invoke<int>(0x26011C78, p0); } // 0x26011C78
   static int _0xC8C0C708(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0xC8C0C708, p0, p1, p2, p3, p4, p5); } // 0xC8C0C708
   static int _0x9A756A72(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<int>(0x9A756A72, p0, p1, p2, p3, p4, p5, p6); } // 0x9A756A72
   static BOOL IS_LAYOUTREF_VALID(Layout layout) { return invoke<BOOL>(0xFC8E55ED, layout); } // 0xFC8E55ED
   static BOOL IS_OBJECT_VALID(Object object) { return invoke<BOOL>(0xD7E7187B, object); } // 0xD7E7187B
   static BOOL IS_ITERATOR_VALID(int iterator) { return invoke<BOOL>(0x5A9CC0B0, iterator); } // 0x5A9CC0B0
   static Any IS_PERS_CHAR_VALID() { return invoke<Any>(0x36CC24A4); } // 0x36CC24A4
   static BOOL IS_POPSET_VALID(Any p0) { return invoke<BOOL>(0x64BAF32C, p0); } // 0x64BAF32C
   static BOOL IS_ZONE_VALID(Any p0) { return invoke<BOOL>(0x262164F8, p0); } // 0x262164F8
   static BOOL IS_CRIME_VALID(Any p0) { return invoke<BOOL>(0x4CC5681D, p0); } // 0x4CC5681D
   static Any GET_OBJECT_TYPE(Any p0) { return invoke<Any>(0x261ECB20, p0); } // 0x261ECB20
   static int _0xADB08F12(Any p0) { return invoke<int>(0xADB08F12, p0); } // 0xADB08F12
   static int _0xA2866F3B(Any p0) { return invoke<int>(0xA2866F3B, p0); } // 0xA2866F3B
   static Layout FIND_NAMED_LAYOUT(const char* layoutName) { return invoke<Layout>(0x5699DE7E, layoutName); } // 0x5699DE7E
   static const char* GET_ACTOR_NAME(Actor actor) { return invoke<const char*>(0x78CF43C1, actor); } // 0x78CF43C1
   static const char* GET_OBJECT_NAME(Object p0) { return invoke<const char*>(0xDF40614F, p0); } // 0xDF40614F
   static const char* GET_LAYOUT_NAME(Object p0) { return invoke<const char*>(0xBADE22A2, p0); } // 0xBADE22A2
   static const char* GET_OBJECT_MODEL_NAME(Any p0) { return invoke<const char*>(0x5C4262F9, p0); } // 0x5C4262F9
   static const char* GET_POPULATION_SET_NAME(Any p0) { return invoke<const char*>(0xF662EAE1, p0); } // 0xF662EAE1
   static int _0x2CF0010F(Any p0) { return invoke<int>(0x2CF0010F, p0); } // 0x2CF0010F
   static Any GET_GRINGO_FROM_OBJECT(Any p0) { return invoke<Any>(0x8A01B64B, p0); } // 0x8A01B64B
   static int _0xA7E9DA22(Any p0) { return invoke<int>(0xA7E9DA22, p0); } // 0xA7E9DA22
   static int _0x111501F7(Any p0) { return invoke<int>(0x111501F7, p0); } // 0x111501F7
   static Any GET_OBJECT_FROM_ACTOR(int* p0, Any p1) { return invoke<Any>(0x4A2063EC, p0, p1); } // 0x4A2063EC
   static Any GET_OBJECT_FROM_VOLUME(int* p0, Any p1) { return invoke<Any>(0xFADF0B96, p0, p1); } // 0xFADF0B96
   static Any GET_OBJECT_FROM_PERS_CHAR(int* p0, Any p1) { return invoke<Any>(0x35B5587D, p0, p1); } // 0x35B5587D
   static Any GET_OBJECT_FROM_SQUAD(int* p0, Any p1) { return invoke<Any>(0xEDA897FA, p0, p1); } // 0xEDA897FA
   static Any GET_OBJECT_FROM_CRIME(int* p0, Any p1) { return invoke<Any>(0x831338D9, p0, p1); }  // 0x831338D9
   static Any GET_OBJECT_FROM_PHYSINST(int* p0, Any p1) { return invoke<Any>(0x0550E178, p0, p1); } // 0x0550E178
   static int GET_ACTOR_FROM_OBJECT(Any p0) { return invoke<int>(0x34F0AD96, p0); } // 0x34F0AD96
   static int _0x502DAC62(Any p0) { return invoke<int>(0x502DAC62, p0); } // 0x502DAC62
   static int _0x024B2FFC(Any p0) { return invoke<int>(0x024B2FFC, p0); } // 0x024B2FFC
   static int _0xF5EE5874(Any p0) { return invoke<int>(0xF5EE5874, p0); } // 0xF5EE5874
   static int _0xD0C471FB(Any p0) { return invoke<int>(0xD0C471FB, p0); } // 0xD0C471FB
   static int GET_LAYOUT_FROM_OBJECT(Any p0) { return invoke<int>(0x51D6DA2C, p0); } // 0x51D6DA2C
   static int _0x6B72661F(Any p0) { return invoke<int>(0x6B72661F, p0); } // 0x6B72661F
   static int _0xB578DB52(Any p0) { return invoke<int>(0xB578DB52, p0); } // 0xB578DB52
   static int GET_CAMERA_FROM_OBJECT(Any p0) { return invoke<int>(0xD4048969, p0); } // 0xD4048969
   static int _0x50A7E334(Any p0) { return invoke<int>(0x50A7E334, p0); } // 0x50A7E334
   static Layout CREATE_LAYOUT(const char* layoutName) { return invoke<Layout>(0x6CA53214, layoutName); } // 0x6CA53214
   static int _0x426828CB(Any p0) { return invoke<int>(0x426828CB, p0); } // 0x426828CB
   static int CREATE_CORPSE_IN_LAYOUT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return invoke<int>(0xE8C04F05, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0xE8C04F05
   static int CREATE_CORPSE_IN_LAYOUT_RANDOM(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return invoke<int>(0x40856E8A, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x40856E8A
   static int CREATE_CORPSE_VARIATION_IN_LAYOUT(Any p0, Any p1) { return invoke<int>(0x2EC081E4, p0, p1); } // 0x2EC081E4
   static int CREATE_CORPSE_VARIATION_IN_LAYOUT_RANDOM(int* p0, Any p1) { return invoke<int>(0x8468286B, p0, p1); } // 0x8468286B
   static int CREATE_COVER_LOCATION_IN_LAYOUT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<int>(0x708C7D7B, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x708C7D7B
   static int _0x44A34042(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<int>(0x44A34042, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x44A34042
   static int _0xF9CC7F63(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<int>(0xF9CC7F63, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xF9CC7F63
   static int _0xA17311E4(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { return invoke<int>(0xA17311E4, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0xA17311E4
   static int _0x177A3843(Any p0, Any p1) { return invoke<int>(0x177A3843, p0, p1); } // 0x177A3843
   static int _0x025C9845(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<int>(0x025C9845, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x025C9845
   static int CREATE_GRINGO_ON_OBJECT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<int>(0x88087384, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x88087384
   static int _0x66A8AF91(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<int>(0x66A8AF91, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x66A8AF91
   static int _0x80FB8BDE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<int>(0x80FB8BDE, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x80FB8BDE
   static int _0x779267C3(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return invoke<int>(0x779267C3, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x779267C3
   static Object CREATE_PROP_IN_LAYOUT(Layout p0, const char* p1, const char* p2, Vector3 p3, Vector3 p4, BOOL p5) { return invoke<Object>(0xE351587D, p0, p1, p2, p3, p4, p5); }	// 0xE351587D
   static int _0xD92BA5B6(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return invoke<int>(0xD92BA5B6, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xD92BA5B6
   static Any _0xAF4F1910(Any p0, Any p1) { return invoke<Any>(0xAF4F1910, p0, p1); }// 0xAF4F1910
   static int _0xB20CA4DF(int* p0, Any p1, Any p2, Any p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10) { return invoke<int>(0xB20CA4DF, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0xB20CA4DF
   static int _0x80B8A1BE(Any p0, Any p1, Any p2) { return invoke<int>(0x80B8A1BE, p0, p1, p2); } // 0x80B8A1BE
   static int _0xB6709FF4(Any p0, Any p1, Any p2) { return invoke<int>(0xB6709FF4, p0, p1, p2); } // 0xB6709FF4
   static int CREATE_OBSTACLE_IN_LAYOUT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return invoke<int>(0x2703760F, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0x2703760F
   static int CREATE_OBSTACLE_ON_OBJECT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return invoke<int>(0x7E81694C, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0x7E81694C
   static int _0xF7277A0F(Any p0, Any p1) { return invoke<int>(0xF7277A0F, p0, p1); } // 0xF7277A0F
   static int _0x91C6AC0E(Any p0, Any p1, Any p2) { return invoke<int>(0x91C6AC0E, p0, p1, p2); } // 0x91C6AC0E
   static int _0xD60032F6(Any p0) { return invoke<int>(0xD60032F6, p0); } // 0xD60032F6
   static int _0xE77F61B2(Any p0, Any p1) { return invoke<int>(0xE77F61B2, p0, p1); } // 0xE77F61B2
   static int _0xA936E73B(Any p0, Any p1) { return invoke<int>(0xA936E73B, p0, p1); } // 0xA936E73B
   static void RELEASE_LAYOUT_REF(Layout layout) { invoke<Void>(0xD9AC8830, layout); } // 0xD9AC8830
   static void RELEASE_LAYOUT_OBJECTS(Layout layout) { invoke<Void>(0xE78E66F0, layout); } // 0xE78E66F0
   static void DESTROY_LAYOUT_OBJECTS(Layout layout) { invoke<Void>(0x28A2A4CC, layout); } // 0x28A2A4CC
   static int _0x000079CB(Any p0) { return invoke<int>(0x000079CB, p0); } // 0x000079CB
   static int _0x3CD2C250(Any p0) { return invoke<int>(0x3CD2C250, p0); } // 0x3CD2C250
   static int _0x7EEC1F40(Any p0, Any p1, Any p2) { return invoke<int>(0x7EEC1F40, p0, p1, p2); } // 0x7EEC1F40
   static int _0xC15C3361(Any p0, Any p1) { return invoke<int>(0xC15C3361, p0, p1); } // 0xC15C3361
   static void MARK_OBJECT_FOR_AGGRESSIVE_CLEANUP(Any p0, Any p1) { invoke<Void>(0x8212247D, p0, p1); } // 0x8212247D
   static void RELEASE_OBJECT_REF(Any p0) { invoke<Void>(0x67DB5ABF, p0); } // 0x67DB5ABF
   static void RELEASE_ACTOR(Actor actor) { invoke<Void>(0x32489AFB, actor); } // 0x32489AFB
   static void RELEASE_VOLUME(Any p0) { invoke<Void>(0x81F984F8, p0); } // 0x81F984F8
   static void RELEASE_PERS_CHAR(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13, Any p14, Any p15, Any p16) { invoke<Void>(0x19C3CF93, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16); } // 0x19C3CF93
   static void DESTROY_VOLUME(Any p0) { invoke<Void>(0x8CAB944F, p0); } // 0x8CAB944F
   static void DESTROY_ACTOR(Actor actor) { invoke<Void>(0x8BD21869, actor); } // 0x8BD21869
   static void DESTROY_LAYOUT(Any p0) { invoke<Void>(0xC1756F39, p0); } // 0xC1756F39
   static void DESTROY_OBJECT(Any p0) { invoke<Void>(0x21144994, p0); } // 0x21144994
   static void DESTROY_ITERATOR(Any p0) { invoke<Void>(0xE284A10C, p0); } // 0xE284A10C
   static int DESTROY_PERS_CHAR(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0x4028CE77, p0, p1, p2, p3, p4, p5); } // 0x4028CE77
   static void DESTROY_POINT_LIGHT(Any p0) { invoke<Void>(0x6BC96263, p0); } // 0x6BC96263
   static void DESTROY_POPULATION_SET(Any p0) { invoke<Void>(0xD064878D, p0); } // 0xD064878D
   static void DESTROY_ZONE(Any p0) { invoke<Void>(0xD62F3D27, p0); } // 0xD62F3D27
   static void DESTROY_CRIME(Any p0) { invoke<Void>(0xE9AB08C0, p0); } // 0xE9AB08C0
   static int _0xCBB2267A(Any p0, Any p1) { return invoke<int>(0xCBB2267A, p0, p1); } // 0xCBB2267A
   static int _0x2D160228(Any p0, Any p1) { return invoke<int>(0x2D160228, p0, p1); } // 0x2D160228
   static int GET_OBJECT_OWNER(Any p0) { return invoke<int>(0x48B36E07, p0); } // 0x48B36E07
   static int* _0x86B0B004(Any p0, Any p1) { return invoke<int*>(0x86B0B004, p0, p1); } // 0x86B0B004
   static int _0x65C3D8F6() { return invoke<int>(0x65C3D8F6); } // 0x65C3D8F6
   static Layout GET_AMBIENT_LAYOUT() { return invoke<Layout>(0xB52A3D48); } // 0xB52A3D48
   static Any _0x76FBF412(Any p0) { return invoke<Any>(0x76FBF412, p0); } // 0x76FBF412
   static Layout _0xADE13224(Any p0) { return invoke<Layout>(0xADE13224, p0); } // 0xADE13224
   static int _0x921B5F2B(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x921B5F2B, p0, p1, p2, p3); } // 0x921B5F2B
   static BOOL IS_OBJECTSET_VALID(Any p0) { return invoke<BOOL>(0x552189FD, p0); } // 0x552189FD
   static int _0x43FBBDE1(Any p0, Any p1) { return invoke<int>(0x43FBBDE1, p0, p1); } // 0x43FBBDE1
   static int GET_OBJECTSET_SIZE(Any p0) { return invoke<int>(0xE09DE8A0, p0); } // 0xE09DE8A0
   static int* GET_OBJECT_FROM_OBJECTSET(Any p0, Any p1) { return invoke<int*>(0xBF680846, p0, p1); }  // 0xBF680846
   static int _0x2CB3B980(Any p0) { return invoke<int>(0x2CB3B980, p0); } // 0x2CB3B980
   static int _0x50D39153(Any p0, Any p1) { return invoke<int>(0x50D39153, p0, p1); } // 0x50D39153
   static BOOL IS_OBJECT_IN_OBJECTSET(Any p0, Any p1) { return invoke<BOOL>(0x0114FCBD, p0, p1); } // 0x0114FCBD
   static void _0xA3E05BAE(Any p0, Any p1) { invoke<Void>(0xA3E05BAE, p0, p1); } // 0xA3E05BAE
   static void CLEAN_OBJECTSET(Any p0) { invoke<Void>(0x11EE07B5, p0); } // 0x11EE07B5
   static void DISBAND_OBJECTSET(Any p0) { invoke<Void>(0x179A07DD, p0); } // 0x179A07DD
   static void DESTROY_OBJECTSET(Any p0) { invoke<Void>(0x3A71A589, p0); } // 0x3A71A589
   static int SET_CORPSE_PERMANENT(Any p0, Any p1) { return invoke<int>(0x5720BF8A, p0, p1); } // 0x5720BF8A
   static BOOL _0x44C07DA5(unsigned int p0) { return invoke<BOOL>(0x44C07DA5, p0); } // 0x44C07DA5
   static int _0x5F66B23E(unsigned int p0, unsigned int p1) { return invoke<int>(0x5F66B23E, p0, p1); } // 0x5F66B23E
   static BOOL IS_OBJECT_IN_VOLUME(Any p0, Any p1) { return invoke<BOOL>(0x2ECF04F3, p0, p1); } // 0x2ECF04F3
   static int _0xCB3F7DA5(int* p0, float p1, float p2, float p3, float p4, int p5, int p6, int p7, int p8, char p9) { return invoke<int>(0xCB3F7DA5, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xCB3F7DA5
   static int _0xA36ED4A6(int* p0, float p1, float p2, float p3, float p4, int p5, int p6, int p7, int p8, char p9) { return invoke<int>(0xA36ED4A6, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xA36ED4A6
   static int _0x6F513950(int* p0, int p1, int p2, int p3, int p4, unsigned int p5, float p6, float p7, float p8, float p9) { return invoke<int>(0x6F513950, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x6F513950
   static int _LOCATE_OBJECTS_IN_VOLUME(unsigned int p0, unsigned int p1, int p2, char p3, int p4, int p5, int p6) { return invoke<int>(0x35C8FD4A, p0, p1, p2, p3, p4, p5, p5, p6); } // 0x35C8FD4A
   static int _LOCATE_OBJECTS_IN_VOLUME_2(unsigned int p0, unsigned int p1, int p2, char p3, int p4, int p5, int p6) { return invoke<int>(0x0F701FF7, p0, p1, p2, p3, p4, p5, p5, p6); } // 0x0F701FF7
   static void SET_VOLUME_PARAMS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0xFEC1CBC6, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xFEC1CBC6
   static int _0xB104FF3E(int p0, int p1) { return invoke<int>(0xB104FF3E, p0, p1); } // 0xB104FF3E
   static int COPY_VOLUME(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x122C916E, p0, p1, p2, p3); } // 0x122C916E
   static void SCALE_VOLUME(Any p0, Any p1) { invoke<Void>(0x14DCF1EF, p0, p1); } // 0x14DCF1EF
   static void SET_ACTOR_STAY_OUTSIDE_OF_VOLUME(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x1229C536, p0, p1, p2, p3); } // 0x1229C536
   static void ADD_ACTOR_STAY_OUTSIDE_OF_VOLUME(Any p0, Any p1) { invoke<Void>(0x617C9630, p0, p1); } // 0x617C9630
   static void SET_ACTOR_STAY_WITHIN_VOLUME(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x6A4A1699, p0, p1, p2, p3); } // 0x6A4A1699
   static void ADD_ACTOR_STAY_WITHIN_VOLUME(Any p0, Any p1) { invoke<Void>(0xCDEF4316, p0, p1); } // 0xCDEF4316
   static int _0xED6D63FE(int p0, int p1, int p2, int p3) { return invoke<int>(0xED6D63FE, p0, p1, p2, p3); } // 0xED6D63FE
   static void SET_ACTOR_VOLUME_PARAMETERS(Actor actor, float value) { invoke<Void>(0x8B46B294, actor, value); } // 0x8B46B294
   static void REMOVE_ACTOR_STAY_WITHIN_VOLUME(Actor actor) { invoke<Void>(0x2974CAF6, actor); } // 0x2974CAF6
   static void REMOVE_ACTOR_STAY_OUTSIDE_OF_VOLUME(Actor actor) { invoke<Void>(0x42EF7DB7, actor); } // 0x42EF7DB7
   static int _0x0E41A6AC(int p0) { return invoke<int>(0x0E41A6AC, p0); } // 0x0E41A6AC
   static int _0x983ED842(int p0) { return invoke<int>(0x983ED842, p0); } // 0x983ED842
   static int _0x43E2808B(int p0) { return invoke<int>(0x43E2808B, p0); } // 0x43E2808B
   static int _0xE9E8C31A(int p0) { return invoke<int>(0xE9E8C31A, p0); } // 0xE9E8C31A
   static int _0x0ACF7E75(int p0) { return invoke<int>(0x0ACF7E75, p0); } // 0x0ACF7E75
   static int _0x80FF115A(int p0) { return invoke<int>(0x80FF115A, p0); } // 0x80FF115A
   static void TOGGLE_COVER_PROPS(Any p0) { invoke<Void>(0x288E4BFB, p0); } // 0x288E4BFB
   static int _0x35E78298(Object p0, int p1) { return invoke<int>(0x35E78298, p0, p1); } // 0x35E78298
   static int CREATE_ZONE_VOLUME(Any p0) { return invoke<int>(0xBB05B731, p0); } // 0xBB05B731
   static int _0x9189EB8B(int* p0, int p1) { return invoke<int>(0x9189EB8B, p0, p1); } // 0x9189EB8B
   static int CREATE_POPULATION_SET(Any p0) { return invoke<int>(0xAF1D570B, p0); } // 0xAF1D570B
   static int _0x0B40BBE3(int* p0, int p1) { return invoke<int>(0x0B40BBE3, p0, p1); } // 0x0B40BBE3
   static int CREATE_NAMED_POPULATION_SET(Any p0, Any p1) { return invoke<int>(0xB0882841, p0, p1); } // 0xB0882841
   static int _0x4251BF6C(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9) { return invoke<int>(0x4251BF6C, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x4251BF6C
   static int _0x64BEDDEA(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10, int p11, int p12, int p13, int p14, int p15, int p16, int p17) { return invoke<int>(0x64BEDDEA, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17); } // 0x64BEDDEA
   static void CREATE_GATEWAY_TYPE(Any p0, Any p1) { invoke<Void>(0x92CC441F, p0, p1); } // 0x92CC441F
   static void SNAP_ACTOR_TO_GRINGO(Actor actor) { invoke<Void>(0xD0A845E9, actor); } // 0xD0A845E9
   static int _0x6745191B(int p0, float p1, float p2, float p3) { return invoke<int>(0x6745191B, p0, p1, p2, p3); } // 0x6745191B
   static int _0x276EFF8E(int p0, float p1, float p2, float p3) { return invoke<int>(0x276EFF8E, p0, p1, p2, p3); } // 0x276EFF8E
   static int _0xE18028C1(int p0) { return invoke<int>(0xE18028C1, p0); } // 0xE18028C1
   static int _0x7246F438(int p0) { return invoke<int>(0x7246F438, p0); } // 0x7246F438
   static int _0x1A59E608(int p0) { return invoke<int>(0x1A59E608, p0); } // 0x1A59E608
   static int _0x0AFC0B99() { return invoke<int>(0x0AFC0B99); } // 0x0AFC0B99
   static int _0x547166A7(int p0) { return invoke<int>(0x547166A7, p0); } // 0x547166A7
   static int _0xF1F8AFCA(int* p0, int p1, int p2, char* p3, float p4, float p5, float p6) { return invoke<int>(0xF1F8AFCA, p0, p1, p2, p3, p4, p5, p6); } // 0xF1F8AFCA
   static int _0xFF8CBD07(int* p0, int p1, int p2, float p3, float p4, float p5) { return invoke<int>(0xFF8CBD07, p0, p1, p2, p3, p4, p5); } // 0xFF8CBD07
   static int _0x2A902148(int* p0, int p1, int p2, int p3, float p4, float p5, float p6) { return invoke<int>(0x2A902148, p0, p1, p2, p3, p4, p5, p6); } // 0x2A902148
   static int _0x39286DE5(int* p0, int p1, int p2, float p3) { return invoke<int>(0x39286DE5, p0, p1, p2, p3); } // 0x39286DE5
   static int _0xD3A523FD(int p0) { return invoke<int>(0xD3A523FD, p0); } // 0xD3A523FD
   static int _0x1A4C98C1(int p0) { return invoke<int>(0x1A4C98C1, p0); } // 0x1A4C98C1
   static int _0x21BCC0A9(int p0) { return invoke<int>(0x21BCC0A9, p0); } // 0x21BCC0A9
   static int _0x5B417C9C(int p0) { return invoke<int>(0x5B417C9C, p0); } // 0x5B417C9C
   static int _0x1E56BAFD(int p0) { return invoke<int>(0x1E56BAFD, p0); } // 0x1E56BAFD
   static int _0xCFE22435(int p0) { return invoke<int>(0xCFE22435, p0); } // 0xCFE22435
   static int ADD_FORMATION_LOCATION(Any p0, Any p1) { return invoke<int>(0xFBB1BCDF, p0, p1); } // 0xFBB1BCDF
   static void GET_FORMATION_LOCATION(Any p0, Any p1, Any p2) { invoke<Void>(0x17FC65A4, p0, p1, p2); } // 0x17FC65A4
   static int _0xBE5D84BF(int p0) { return invoke<int>(0xBE5D84BF, p0); } // 0xBE5D84BF
   static Any GET_CRIME_POSITION(Any p0) { return invoke<Any>(0x391475E3, p0); } // 0x391475E3
   static Any GET_CRIME_TYPE(Any p0) { return invoke<Any>(0xDB2BDEA8, p0); } // 0xDB2BDEA8
   static float _0xA2DA4D24(int p0) { return invoke<float>(0xA2DA4D24, p0); } // 0xA2DA4D24
   static float _0xD96DBABD(int p0) { return invoke<float>(0xD96DBABD, p0); } // 0xD96DBABD
   static int _0xE07C2D99(int p0) { return invoke<int>(0xE07C2D99, p0); } // 0xE07C2D99
   static Any GET_CRIME_CRIMINAL(Any p0) { return invoke<Any>(0xEC2C34A4, p0); } // 0xEC2C34A4
   static int GET_CRIME_VICTIM(Any p0) { return invoke<int>(0xD2FD7CB6, p0); } // 0xD2FD7CB6
   static int _0x67F224B4(Any* p0, unsigned int p1) { return invoke<int>(0x67F224B4, p0, p1); } // 0x67F224B4
   static int GET_CRIME_FACTION(Any p0) { return invoke<int>(0xE2FE0673, p0); } // 0xE2FE0673
   static Any GET_CRIME_COUNTER(Any p0) { return invoke<Any>(0xB52BA7E6, p0); } // 0xB52BA7E6
   static BOOL _0x72A048B7(unsigned int p0) { return invoke<BOOL>(0x72A048B7, p0); } // 0x72A048B7
   static BOOL IS_CRIME_IN_PROGRESS(unsigned int p0) { return invoke<BOOL>(0x85C58BE1, p0); } // 0x85C58BE1
   static Any GET_CRIME_OBJECTSET(Any p0) { return invoke<Any>(0x72C52B55, p0); } // 0x72C52B55
   static Any SET_CRIME_OBJECTSET(Any p0, Any p1) { return invoke<Any>(0xD60B8F77, p0, p1); } // 0xD60B8F77
   static Any SET_CRIME_POSITION(Any p0, Any p1) { return invoke<Any>(0xB3F4043B, p0, p1); } // 0xB3F4043B
   static Any SET_CRIME_TYPE(Any p0, Any p1) { return invoke<Any>(0x85425011, p0, p1); } // 0x85425011
   static int _0x2AE7D51F(Any p0, float p1) { return invoke<int>(0x2AE7D51F, p0, p1); } // 0x2AE7D51F
   static int _0x898B00F4(unsigned int p0, float p1) { return invoke<int>(0x898B00F4, p0, p1); } // 0x898B00F4
   static int _0x6761D53A(unsigned int p0, int p1) { return invoke<int>(0x6761D53A, p0, p1); } // 0x6761D53A
   static Any SET_CRIME_CRIMINAL(Any p0, Any p1) { return invoke<Any>(0xBA02916B, p0, p1); } // 0xBA02916B
   static void SET_CRIME_VICTIM(Any p0, Any p1) { invoke<Void>(0x7B917033, p0, p1); } // 0x7B917033
   static int _0x8521A685(unsigned int p0, int p1) { return invoke<int>(0x8521A685, p0, p1); } // 0x8521A685
   static void SET_CRIME_FACTION(Any p0, Any p1) { invoke<Void>(0x1E552B26, p0, p1); } // 0x1E552B26
   static Any SET_CRIME_COUNTER(Any p0, Any p1) { return invoke<Any>(0xCC14DC8D, p0, p1); } // 0xCC14DC8D
   static int _0x54E7F26B(unsigned int p0, char p1) { return invoke<int>(0x54E7F26B, p0, p1); } // 0x54E7F26B
   static int _0x2D6CD106(unsigned int p0, char p1) { return invoke<int>(0x2D6CD106, p0, p1); } // 0x2D6CD106
   static int CREATE_OBJECT_ITERATOR(Layout layout) { return invoke<int>(0xD8A12B74, layout); } // 0xD8A12B74
   static int CREATE_NAMED_OBJECT_ITERATOR(Any* p0, int p1, int p2, int p3, int p4, int p5) { return invoke<int>(0x2F358B89, p0, p1, p2, p3, p4, p5); } // 0x2F358B89
   static Object START_OBJECT_ITERATOR(int iterator) { return invoke<Object>(0xE96A0318, iterator); } // 0xE96A0318
   static int OBJECT_ITERATOR_NEXT(int iterator) { return invoke<int>(0xD88DC865, iterator); } // 0xD88DC865
   static int OBJECT_ITERATOR_PREV(int iterator) { return invoke<int>(0x91A3A831, iterator); } // 0x91A3A831
   static int OBJECT_ITERATOR_CURRENT(int iterator) { return invoke<int>(0x191E32C0, iterator); } // 0x191E32C0
   static void OBJECT_ITERATOR_RESET(Any p0) { invoke<Void>(0x351A482F, p0); } // 0x351A482F
   static void ITERATE_ON_PARTIAL_NAME(Any p0, Any p1) { invoke<Void>(0x9624A938, p0, p1); } // 0x9624A938
   static void ITERATE_ON_PARTIAL_MODEL_NAME(Any p0, Any p1) { invoke<Void>(0xD117DF0D, p0, p1); } // 0xD117DF0D
   static void ITERATE_ON_OBJECT_TYPE(int iterator, int type) { invoke<Void>(0xBE553F84, iterator, type); } // 0xBE553F84
   static int ITERATE_IN_AREA(Any p0, float p1, float p2, float p3, float p4, float p5, float p6) { return invoke<int>(0xD7A370D5, p0, p1, p2, p3, p4, p5, p6); } // 0xD7A370D5
   static void ITERATE_IN_SPHERE(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x2243FA6E, p0, p1, p2, p3, p4); } // 0x2243FA6E
   static void ITERATE_IN_VOLUME(Any p0, Any p1) { invoke<Void>(0x6914D904, p0, p1); } // 0x6914D904
   static void ITERATE_EVERYWHERE(Any p0) { invoke<Void>(0xF35C5859, p0); } // 0xF35C5859
   static void ITERATE_IN_LAYOUT(Any p0, Any p1) { invoke<Void>(0xF3ABE99C, p0, p1); } // 0xF3ABE99C
   static void ITERATE_IN_SET(int iterator, int iterationSet) { invoke<Void>(0xDF6B5E94, iterator, iterationSet); } // 0xDF6B5E94
   static void ITERATE_IN_EVENT_TRAP(int p0, int p1) { invoke<Void>(0x0D8BA78E, p0, p1); } // 0x0D8BA78E
   static void _0x8BCB6B86(int p0, int p1) { invoke<Void>(0x8BCB6B86, p0, p1); }  // 0x8BCB6B86
   static int GET_ITERATOR_PARENT(Any p0) { return invoke<int>(0x12AA009F, p0); } // 0x12AA009F
   static int GET_NUM_ITERATOR_MATCHES(int iterator) { return invoke<int>(0xA3874D8A, iterator); } // 0xA3874D8A
   static int FIND_OBJECT_IN_OBJECT(Any p0, Any p1) { return invoke<int>(0x070F9693, p0, p1); } // 0x070F9693
   static Object FIND_OBJECT_IN_LAYOUT(Layout p0, const char* p1) { return invoke<Object>(0xCF875EFA, p0, p1); } // 0xCF875EFA
   static Actor FIND_ACTOR_IN_LAYOUT(Layout layout, const char* actorName) { return invoke<Actor>(0x53A761DE, layout, actorName); } // 0x53A761DE
   static int _0xAC830865(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0xAC830865, p0, p1, p2, p3, p4, p5); } // 0xAC830865
   static int _OBJECT_ITERATOR(float p0, float p1, float p2, float p3, Any p4, Any p5, Any p6, Any p7) { return invoke<int>(0xC9365FBC, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xC9365FBC
   static int _OBJECT_ITERATOR_2(Any p0, Any p1) { return invoke<int>(0xBB77E597, p0, p1); } // 0xBB77E597
   static Any GET_OBJECT_POSITION(Any p0, Any p1) { return invoke<Any>(0x31201B4C, p0, p1); } // 0x31201B4C
   static int _0x3C45D66A(Any p0, Any p1, float p2) { return invoke<int>(0x3C45D66A, p0, p1, p2); } // 0x3C45D66A
   static int GET_OBJECT_AXIS(Any p0, Any p1, Any p2) { return invoke<int>(0xCE412E46, p0, p1, p2); } // 0xCE412E46
   static int GET_OBJECT_RELATIVE_POSITION(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x2243EA59, p0, p1, p2, p3, p4); } // 0x2243EA59
   static int GET_OBJECT_RELATIVE_OFFSET(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x15CDF203, p0, p1, p2, p3, p4); } // 0x15CDF203
   static int GET_OBJECT_RELATIVE_ORIENTATION(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x919583DC, p0, p1, p2, p3, p4); } // 0x919583DC
   static int _0x6689F85C(Any p0, float p1, float p2, float p3, Any p4, Any p5, Any p6) { return invoke<int>(0x6689F85C, p0, p1, p2, p3, p4, p5, p6); } // 0x6689F85C
   static int _0xFC718FC5(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0xFC718FC5, p0, p1, p2, p3, p4, p5); } // 0xFC718FC5
   static int _0x663F1464(Any p0, float p1, float p2, float p3, Any p4, Any p5, Any p6) { return invoke<int>(0x663F1464, p0, p1, p2, p3, p4, p5, p6); } // 0x663F1464
   static int GET_OBJECT_ORIENTATION(Any p0, Any p1) { return invoke<int>(0x27B7D6D6, p0, p1); } // 0x27B7D6D6
   static int GET_OBJECT_HEADING(Any p0) { return invoke<int>(0x1C02D2F8, p0); } // 0x1C02D2F8
   static int SET_OBJECT_POSITION(Object Obj, Vector3 Position) { return invoke<int>(0xC5D796F8, Obj, Position); } // 0xC5D796F8
   static int SET_OBJECT_POSITION_ON_GROUND(Object Obj, Vector3 Position) { return invoke<int>(0x5AB0BBA6, Obj, Position); } // 0x5AB0BBA6
   static int SET_OBJECT_ORIENTATION(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xC8A4EE74, p0, p1, p2, p3); } // 0xC8A4EE74
   static int _0xF437B3D9(Any p0, float p1, float p2) { return invoke<int>(0xF437B3D9, p0, p1, p2); } // 0xF437B3D9
   static int GET_OBJECT_NAMED_BONE_POSITION(Any p0, Any p1, Any p2) { return invoke<int>(0x30516389, p0, p1, p2); } // 0x30516389
   static Any GET_OBJECT_NAMED_BONE_ORIENTATION(Any p0, Any p1) { return invoke<Any>(0xCAD543AD, p0, p1); } // 0xCAD543AD
   static int _0x8C0E3E29(Any p0, Any p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8) { return invoke<int>(0x8C0E3E29, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x8C0E3E29
   static BOOL IS_OBJECT_ATTACHED(Any p0) { return invoke<BOOL>(0xAD08BA79, p0); } // 0xAD08BA79
   static int _GET_OBJECT_ATTACHMENT(Any* p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0x78B73E47, p0, p1, p2, p3, p4, p5); } // 0x78B73E47
   static int GET_OBJECT_ATTACHED_TO(Any p0) { return invoke<int>(0x533475AE, p0); } // 0x533475AE
   static int ATTACH_OBJECTS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return invoke<int>(0xE1421B42, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xE1421B42
   static int _0xCC277C0A(Any* p0, Any p1, Any p2, Any p3, float p4, float p5, float p6, float p7, float p8, float p9) { return invoke<int>(0xCC277C0A, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xCC277C0A
   static int ATTACH_OBJECTS_USING_LOCATOR(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0xB6506558, p0, p1, p2, p3, p4); } // 0xB6506558
   static int ATTACH_OBJECTS_CONTINUOUS(Any p0, Any p1, Any p2) { return invoke<int>(0x319D70BD, p0, p1, p2); } // 0x319D70BD
   static int _0x1D711058(Any* p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x1D711058, p0, p1, p2, p3, p4); } // 0x1D711058
   static int _0x325F7E50(Any p0, float p1, float p2, float p3, float p4, float p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return invoke<int>(0x325F7E50, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0x325F7E50
   static Any IS_ATTACHMENT_VALID(Any p0) { return invoke<Any>(0x50305244, p0); } // 0x50305244
   static void REMOVE_OBJECT_ATTACHMENT(Any p0) { invoke<Void>(0xE894DC13, p0); } // 0xE894DC13
   static int _0x67FC68DB(Any p0) { return invoke<int>(0x67FC68DB, p0); } // 0x67FC68DB
   static int _0x8FB32562(Any p0) { return invoke<int>(0x8FB32562, p0); } // 0x8FB32562
   static int _0x2F7B457B(int p0, float p1, float p2, float p3) { return invoke<int>(0x2F7B457B, p0, p1, p2, p3); } // 0x2F7B457B
   static int _0xD4A54348(int p0, float p1, float p2, float p3) { return invoke<int>(0xD4A54348, p0, p1, p2, p3); } // 0xD4A54348
   static int _0xA870B28E(int p0, char p1) { return invoke<int>(0xA870B28E, p0, p1); } // 0xA870B28E
   static void REFERENCE_OBJECT(Any p0) { invoke<Void>(0x3EEA78A8, p0); } // 0x3EEA78A8
   static void REFERENCE_ACTOR(Any p0) { invoke<Void>(0xE9AABF2F, p0); } // 0xE9AABF2F
   static void DEREFERENCE_OBJECT(Any p0) { invoke<Void>(0xCEA40973, p0); } // 0xCEA40973
   static void DEREFERENCE_ACTOR(Any p0) { invoke<Void>(0x92339B5E, p0); } // 0x92339B5E
   static int _0xCBA75200(int p0, int p1, int p2) { return invoke<int>(0xCBA75200, p0, p1, p2); } // 0xCBA75200
   static int _0x88FD9623(int p0, int p1, int p2) { return invoke<int>(0x88FD9623, p0, p1, p2); } // 0x88FD9623
   static int _0x192973A0(int p0, int p1, int p2) { return invoke<int>(0x192973A0, p0, p1, p2); } // 0x192973A0
   static int _0x4D42E285(int p0, int p1, int p2) { return invoke<int>(0x4D42E285, p0, p1, p2); } // 0x4D42E285
   static int _0xE694F53A(int p0, int p1, int p2) { return invoke<int>(0xE694F53A, p0, p1, p2); } // 0xE694F53A
   static int _0x6D0B8619(int p0, int p1, int p2) { return invoke<int>(0x6D0B8619, p0, p1, p2); } // 0x6D0B8619
   static int _0x807B9519(int p0, int p1, int p2) { return invoke<int>(0x807B9519, p0, p1, p2); } // 0x807B9519
   static int _0x1904CC1D(int p0, int p1, int p2) { return invoke<int>(0x1904CC1D, p0, p1, p2); } // 0x1904CC1D
   static int _0x1957B498(int p0, int p1, int p2) { return invoke<int>(0x1957B498, p0, p1, p2); } // 0x1957B498
   static int _0x05195632(int p0, int p1, int p2) { return invoke<int>(0x05195632, p0, p1, p2); } // 0x05195632
   static int _0x10BD98C9(int p0, int p1, int p2) { return invoke<int>(0x10BD98C9, p0, p1, p2); } // 0x10BD98C9
   static int _0x8A4F9046(int p0, int p1, int p2) { return invoke<int>(0x8A4F9046, p0, p1, p2); } // 0x8A4F9046
   static int _0x495026DA(int p0, int p1, int p2) { return invoke<int>(0x495026DA, p0, p1, p2); } // 0x495026DA
   static int _0x8C9721D6(int p0, int p1, int p2) { return invoke<int>(0x8C9721D6, p0, p1, p2); } // 0x8C9721D6
   static int _0xF2140DEE(int p0) { return invoke<int>(0xF2140DEE, p0); } // 0xF2140DEE
   static BOOL _0x9B903F45(int p0) { return invoke<int>(0x9B903F45, p0); } // 0x9B903F45
   static int _0x16D1E1B4(int p0) { return invoke<int>(0x16D1E1B4, p0); } // 0x16D1E1B4
   static int _0xC741F051(int p0) { return invoke<int>(0xC741F051, p0); } // 0xC741F051
   static Actor CREATE_ACTOR_IN_LAYOUT(Layout layout, const char* actorName, int actorID, float x, float y, float z, float rotx, float roty, float rotz) { return invoke<Actor>(0x8D67F397, layout, actorName, actorID, x, y, z, rotx, roty, rotz); } // 0x8D67F397
   static int _0x6A307D5F(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9) { return invoke<int>(0x6A307D5F, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x6A307D5F
   static Any CREATE_PERS_CHAR_IN_LAYOUT(Any p0, Any p1, Any p2, Any p3, Any p5, Any p6) { return invoke<Any>(0x013B3937, p1, p2, p3, p5, p6); } // 0x013B3937
   static Any _CREATE_ENUMERATED_ACTOR_IN_LAYOUT_USING_VARIABLE_INDEX(Any p0) { return invoke<Any>(0xCCC0A3F3, p0); } // 0xCCC0A3F3
   static Actor _CREATE_ENUMERATED_PLAYER_ACTOR_IN_LAYOUT(Layout layout, Actor actor, const char* actorInLayout, int actorID, float x, float y, float z, float xRot, float yRot, float zRot, int unk0) { return invoke<Actor>(0x637E446B, layout, actor, actorInLayout, actorID, x, y, x, xRot, yRot, zRot, unk0); } // 0x637E446B
   static Any IS_ACTOR_INITED(Any p0) { return invoke<Any>(0x24F4DAB2, p0); } // 0x24F4DAB2
   static Any GET_ACTOR_ENUM(Any p0) { return invoke<Any>(0x0B28E9EC, p0); } // 0x0B28E9EC
   static int GET_ACTOR_ENUM_STRING(Any p0) { return invoke<int>(0xD98CB6F6, p0); } // 0xD98CB6F6
   static int _0xC739D1D2(int p0) { return invoke<int>(0xC739D1D2, p0); } // 0xC739D1D2
   static int _0x990614C1(int p0) { return invoke<int>(0x990614C1, p0); } // 0x990614C1
   static int _0xB50E95D7(int p0) { return invoke<int>(0xB50E95D7, p0); } // 0xB50E95D7
   static int GET_ACTOR_ENUM_FACTION() { return invoke<int>(0x2803BDA8); } // 0x2803BDA8
   static int _0x7AB17813(int p0) { return invoke<int>(0x7AB17813, p0); } // 0x7AB17813
   static void _SET_PLAYER_TO_ENUM(Actor actor, float value) { invoke<Void>(0x95FBA0B0, actor, value); } // 0x95FBA0B0
   static void TURN_ACTOR_INTO_ZOMBIE(Actor actor, Any p1) { invoke<Void>(0x39928706, actor, p1); } // 0x39928706
   static void _0x12A86E9D(int p0) { invoke<Void>(0x12A86E9D, p0); } // 0x12A86E9D
   static void _0x5613615B(int p0) { invoke<Void>(0x5613615B, p0); } // 0x5613615B
   static int _0xB54567B9(int p0) { return invoke<int>(0xB54567B9, p0); } // 0xB54567B9
   static int REQUEST_ASSET(const char* assetDir, int assetType) { return invoke<int>(0x9AA02DA7, assetDir, assetType); }; // 0x9AA02DA7
   static Any GET_ASSET_ID(Any p0) { return invoke<Any>(0x6005B514, p0); } // 0x6005B514
   static int REMOVE_ASSET(Any p0, Any p1) { return invoke<int>(0xE7829D28, p0, p1); }; // 0xE7829D28
   static Any _GET_TYPE_ID_USING_ACTOR_ENUM(Any p0) { return invoke<Any>(0x55E6227E, p0); } // 0x55E6227E
   static Any GET_ASSET_NAME(Any p0) { return invoke<Any>(0x9EDBBB84, p0); } // 0x9EDBBB84
   static BOOL _0x214AFB8C(int p0) { return invoke<BOOL>(0x214AFB8C, p0); } // 0x214AFB8C
   static BOOL _IS_TYPE_ID_VALID_BY_STRING(Any p0, int p1, int p2, int p3, int p4) { return invoke<BOOL>(0xFDF42AAC, p0, p1, p2, p3, p4); } // 0xFDF42AAC
   static int _0x1FCC8FEF(int p0) { return invoke<int>(0x1FCC8FEF, p0); } // 0x1FCC8FEF
   static int _0xAF2597E8(int p0, int p1) { return invoke<int>(0xAF2597E8, p0, p1); } // 0xAF2597E8
   static int _0x97951004(int p0) { return invoke<int>(0x97951004, p0); } // 0x97951004
   static int REQUEST_FIXED_CORPSE(Any p0, Any p1) { return invoke<int>(0x0D447878, p0, p1); } // 0x0D447878
   static int _0xCEC355CE(int p0, int p1) { return invoke<int>(0xCEC355CE, p0, p1); } // 0xCEC355CE
   static int _0x418A22D5(int p0, int p1) { return invoke<int>(0x418A22D5, p0, p1); } // 0x418A22D5
   static int _0x77403213(int p0, int p1, int p2) { return invoke<int>(0x77403213, p0, p1, p2); } // 0x77403213
   static int _0x601FC9F4(int p0, int p1) { return invoke<int>(0x601FC9F4, p0, p1); } // 0x601FC9F4
   static int _0x05D69EA6(int p0, int p1) { return invoke<int>(0x05D69EA6, p0, p1); } // 0x05D69EA6
   static int _0x9AC1CA75(int p0, int p1, int p2) { return invoke<int>(0x9AC1CA75, p0, p1, p2); } // 0x9AC1CA75
   static int SET_PROP_AI_OBSTACLE_ENABLED(Any p0, Any p1) { return invoke<int>(0x0DC83543, p0, p1); } // 0x0DC83543
   static int _0x49D0DF2E(Any p0) { return invoke<int>(0x49D0DF2E, p0); } // 0x49D0DF2E
   static void _0xDF93BD7C(Any p0) { invoke<Void>(0xDF93BD7C, p0); } // 0xDF93BD7C
   static void DESTROY_CAMERA(Any p0) { invoke<Void>(0x767E08D0, p0); } // 0x767E08D0
   static void DESTROY_CAMERA_SHOT(Actor actor) { invoke<Void>(0x59C2DC62, actor); } // 0x59C2DC62
   static Any CREATE_WORLD_SECTOR(Any p0, Any p1) { return invoke<Any>(0xC94CC336, p0, p1); } // 0xC94CC336
   static BOOL IS_WORLD_SECTOR_LOADED(Any p0) { return invoke<BOOL>(0xBF81A6C4, p0); } // 0xBF81A6C4
   static void MARK_REGION_READY(Any p0) { invoke<Void>(0x276A420B, p0); } // 0x276A420B
   static int _0xA5F229C9(Any p0, Any p1, Any p2) { return invoke<int>(0xA5F229C9, p0, p1, p1); } // 0xA5F229C9
   static int _0x0F146D2C(Any p0) { return invoke<int>(0x0F146D2C, p0); } // 0x0F146D2C
   static int _0xF46FC138() { return invoke<int>(0xF46FC138); } // 0xF46FC138
   static int _0x03B2D067(Any p0) { return invoke<int>(0x03B2D067, p0); } // 0x03B2D067
   static void _0x6C526E7B(Any p0) { invoke<Void>(0x6C526E7B, p0); } // 0x6C526E7B
   static int _0xC1195126(Any p0) { return invoke<int>(0xC1195126, p0); } // 0xC1195126
   static int _0x00CDD849(Any p0) { return invoke<int>(0x00CDD849, p0); } // 0x00CDD849
   static int _0x6138B1B8(Any p0) { return invoke<int>(0x6138B1B8, p0); } // 0x6138B1B8
   static int _0xCE081203(Any p0) { return invoke<int>(0xCE081203, p0); } // 0xCE081203
   static int _0xBF6E9855() { return invoke<int>(0xBF6E9855); } // 0xBF6E9855
   static int _0x4193D42F() { return invoke<int>(0x4193D42F); } // 0x4193D42F
   static void _0xF037DCA2(Any p0) { invoke<Void>(0xF037DCA2, p0); } // 0xF037DCA2
   static void SET_TOWN_DENSITY(Any p0) { invoke<Void>(0x3748F199, p0); } // 0x3748F199
   static void _0x03CD9C87(Any p0, Any p1) { invoke<Void>(0x03CD9C87, p0); } // 0x03CD9C87
   static int _0x43FF4632(Any p0) { return invoke<int>(0x43FF4632, p0); } // 0x43FF4632
}

namespace LEASH
{
   static int CREATE_LEASH_OBJECT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0x9BCC06E2, p0, p1, p2, p3, p4, p5); } // 0x9BCC06E2
   static int LEASH_CONSTRAIN(Any p0) { return invoke<int>(0x8EA68EB5, p0); } // 0x8EA68EB5
   static Any LEASH_RESTART(Any p0) { return invoke<Any>(0xE58339B3, p0); } // 0xE58339B3
   static int _0x7F190CA3(Any p0) { return invoke<int>(0x7F190CA3, p0); }  // 0x7F190CA3
   static int _0x14BEC6F5(Any p0) { return invoke<int>(0x14BEC6F5, p0); }  // 0x14BEC6F5
   static int LEASH_RELEASE_CONSTRAINT(Any p0) { return invoke<int>(0x7A1376B0, p0); } // 0x7A1376B0
   static int LEASH_ATTACH_TO_WORLD(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<int>(0x0FCDB481, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x0FCDB481
   static int LEASH_ATTACH_TO_OBJECT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return invoke<int>(0x35D8B21E, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0x35D8B21E
   static int _0xE782EB20(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return invoke<int>(0xE782EB20, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0xE782EB20
   static int _0x82A73B3D(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { return invoke<int>(0x82A73B3D, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0x82A73B3D
   static int _0x4B67B8BB(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11) { return invoke<int>(0x4B67B8BB, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0x4B67B8BB
   static int _0xC1265E7F(Any p0, Any p1, float p2, float p3, float p4) { return invoke<int>(0xC1265E7F, p0, p1, p2, p3, p4); } // 0xC1265E7F
   static int LEASH_DETACH_OBJECT(Any p0) { return invoke<int>(0x951B8DF7, p0); } // 0x951B8DF7
   static int LEASH_IS_BROKEN(Any p0) { return invoke<int>(0x46BE1D43, p0); } // 0x46BE1D43
   static Any LEASH_BREAK(Any p0, Any p1) { return invoke<Any>(0x8640261B, p0, p1); } // 0x8640261B
   static int _0xC039BBF1(Any p0, Any p1, Any p2) { return invoke<int>(0xC039BBF1, p0, p1, p2); } // 0xC039BBF1
   static int _0x51CF9A54(Any p0, Any p1, Any p2) { return invoke<int>(0x51CF9A54, p0, p1, p2); } // 0x51CF9A54
   static int _0x5A72DD49(Any p0, Any p1) { return invoke<int>(0x5A72DD49, p0, p1); } // 0x5A72DD49
   static int _0x1A8494E6(Any p0, Any p1) { return invoke<int>(0x1A8494E6, p0, p1); } // 0x1A8494E6
}

namespace MEMORY
{
   static void MEMORY_CLEAR_EVENTS(Any p0, Any p1) { invoke<Void>(0x8CD37E9E, p0, p1); } // 0x8CD37E9E
   static void MEMORY_CLEAR_ALL(Any p0) { invoke<Void>(0x4485B246, p0); } // 0x4485B246
   static void MEMORY_CONSIDER_ACCORDING_TO_FACTION(Any p0, Any p1) { invoke<Void>(0xACD4084D, p0, p1); } // 0xACD4084D
   static void MEMORY_CONSIDER_AS(Any p0, Any p1, Any p2) { invoke<Void>(0x296C01A4, p0, p1, p2); } // 0x296C01A4
   static void MEMORY_CONSIDER_AS_ENEMY(Any p0, Any p1) { invoke<Void>(0x745A1BA3, p0, p1); } // 0x745A1BA3
   static int MEMORY_GET_IS_IDENTIFIED(Any p0, Any p1) { return invoke<Void>(0x0810A7BA, p0, p1); } // 0x0810A7BA
   static int MEMORY_GET_IS_VISIBLE(Any p0, Any p1) { return invoke<int>(0x45CE40FD, p0, p1); } // 0x45CE40FD
   static int MEMORY_GET_WAS_VISIBLE_WITHIN_TIME(Any p0, Any p1, Any p2) { return invoke<int>(0xC407497F, p0, p1, p2); } // 0xC407497F
   static void MEMORY_IDENTIFY(Any p0, Any p1) { invoke<Void>(0xBA09085C, p0, p1); } // 0xBA09085C
   static void MEMORY_REPORT_POSITION(Any p0, Any p1, Any p2) { invoke<Void>(0x052CC7CE, p0, p1, p2); } // 0x052CC7CE
   static void MEMORY_REPORT_POSITION_AUTO(Any p0, Any p1, Any p2) { invoke<Void>(0x2F589CDF, p0, p1, p2); } // 0x2F589CDF
   static int MEMORY_GET_MUST_IDENTIFY(Any p0, Any p1) { return invoke<int>(0x05B3D34F, p0, p1); } // 0x05B3D34F
   static void MEMORY_ATTACK_ON_SIGHT(Any p0, Any p1) { invoke<Void>(0x5A83A1EA, p0, p1); } // 0x5A83A1EA
   static void MEMORY_CLEAR_RIDING_PREFERENCE(Any p0) { invoke<Void>(0x48AA959E, p0); } // 0x48AA959E
   static void MEMORY_PREFER_RIDING(Any p0, Any p1) { invoke<Void>(0x1B72B0DD, p0, p1); } // 0x1B72B0DD
   static void MEMORY_PREFER_WALKING(Any p0, Any p1) { invoke<Void>(0x2F7B60A4, p0, p1); } // 0x2F7B60A4
   static void MEMORY_PREFER_MELEE(Any p0, Any p1) { invoke<Void>(0x2F929ECD, p0, p1); } // 0x2F929ECD
   static void _MEMORY_PREFER_MELEE_2(Any p0, Any p1) { invoke<Void>(0xC175F2B5, p0, p1); } // 0xC175F2B5
   static void MEMORY_ALLOW_SHOOTING(Any p0, Any p1) { invoke<Void>(0x937E1760, p0, p1); } // 0x937E1760
   static void MEMORY_ALLOW_TAKE_COVER(Any p0, Any p1) { invoke<Void>(0xE944E5F8, p0, p1); } // 0xE944E5F8
   static void MEMORY_ALLOW_THROWING_EXPLOSIVES(Any p0, Any p1) { invoke<Void>(0xDBDB57D0, p0, p1); } // 0xDBDB57D0
   static int MEMORY_ALLOW_PICKUP_WEAPONS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0x5DD0AC4A, p0, p1, p2, p3, p4, p5); } // 0x5DD0AC4A
   static int MEMORY_GET_WEAPON_DRAW_PREFERENCE(Any p0) { return invoke<int>(0x009EB4C1, p0); } // 0x009EB4C1
   static void MEMORY_CLEAR_WEAPON_DRAW_PREFERENCE(Any p0) { invoke<Void>(0xDD965D74, p0); } // 0xDD965D74
   static void MEMORY_SET_WEAPON_DRAW_PREFERENCE(Any p0, Any p1) { invoke<Void>(0xF8CB6260, p0, p1); } // 0xF8CB6260
   static int MEMORY_GET_POSITION_LAST_KNOWN_TIME(Any p0, Any p1) { return invoke<int>(0x7E77DD6C, p0, p1); } // 0x7E77DD6C
   static void _AI_GLOBAL_CLEAR_DANGER_2(Any p0) { invoke<Void>(0x7EDD316C, p0); } // 0x7EDD316C
   static void _0xD1628C57() { invoke<Void>(0xD1628C57); } // 0xD1628C57
   static void MEMORY_SHOULD_ALWAYS_PATHFIND_IN_FORMATION(Any p0, Any p1) { invoke<Void>(0x052E865C, p0, p1); } // 0x052E865C
   static void _0xAF94B7D9() { invoke<Void>(0xAF94B7D9); } // 0xAF94B7D9
   static void AI_GLOBAL_CLEAR_DANGER(Any p0) { invoke<Void>(0xB6FCFFAA, p0); } // 0xB6FCFFAA
   static int AI_GLOBAL_GET_PERMANENT_DANGER(Any p0) { return invoke<int>(0xFF00B4E6, p0); } // 0xFF00B4E6
   static int AI_GLOBAL_IS_DANGER(Any p0, Any p1) { return invoke<int>(0x5EC098F2, p0, p1); } // 0x5EC098F2
   static void AI_GLOBAL_SET_PERMANENT_DANGER(Any p0, Any p1) { invoke<Void>(0x64C177FB, p0, p1); } // 0x64C177FB
   static void AI_GLOBAL_REPORT_DANGER(Any p0) { invoke<Void>(0xCF70330C, p0); } // 0xCF70330C
   static int MEMORY_SET_UNARMED_RETREAT(Any p0) { return invoke<int>(0xB4621962, p0); } // 0xB4621962
}

namespace MINIGAME
{
   static void START_MINIGAME(Any p0) { invoke<Void>(0xE8184916, p0); } // 0xE8184916
   static int PUSH_MINIGAME_INPUT(Any p0) { return invoke<int>(0xE2B894D1, p0); } // 0xE2B894D1
   static BOOL IS_MINIGAME_RUNNING() { return invoke<BOOL>(0x117D7E71); } // 0x117D7E71
   static void END_CURRENT_MINIGAME() { invoke<Void>(0xCA746CD2); } // 0xCA746CD2
   static int _0x6AAD0420(Any p0, Any p1, float p2, Any p3, Any p4) { return invoke<int>(0x6AAD0420, p0, p1, p2, p3, p4); } // 0x6AAD0420
   static Any _0x655D350B(Any p0, Any p1, Any p2) { return invoke<Any>(0x655D350B, p0, p1, p2); } // 0x655D350B
   static int _0x0627DDEC(Any p0, Any p1) { return invoke<int>(0x0627DDEC, p0, p1); } // 0x0627DDEC
   static int _0x2DC768BB(const char* p0) { return invoke<int>(0x2DC768BB, p0); } // 0x2DC768BB
   static int _0x8275FDD4(Any p0) { return invoke<int>(0x8275FDD4, p0); } // 0x8275FDD4
}

namespace MIXER
{
   static void DYNAMICMIXER_TRIGGERSTATE(Any p0) { invoke<Void>(0xECD8E116, p0); } // 0xECD8E116
   static void _DYNAMICMIXER_1(Any p0, int* p1) { invoke<Void>(0xA82D893C, p0, p1); } // 0xA82D893C
   static void DYNAMICMIXER_DETRIGGERSTATE(Any p0) { invoke<Void>(0xF86010D1, p0); } // 0xF86010D1
   static int _DYNAMICMIXER_2() { return invoke<int>(0xADCC16A2); } // 0xADCC16A2
}

namespace MOUNT
{
   static void SET_MOST_RECENT_MOUNT(Any p0, Any p1) { invoke<Void>(0x00AF2CB0, p0, p1); } // 0x00AF2CB0
   static Any GET_MOST_RECENT_MOUNT(Actor actor) { return invoke<Any>(0x708E450F, actor); } // 0x708E450F
   static Any GET_MOST_RECENT_RIDER(Actor actor) { return invoke<Any>(0x668E55C3, actor); } // 0x668E55C3
   static BOOL IS_ACTOR_HORSE(Actor actor) { return invoke<BOOL>(0xDB0D0478, actor); } // 0xDB0D0478
   static BOOL IS_ACTOR_MULE(Actor actor) { return invoke<BOOL>(0x1F739295, actor); } // 0x1F739295
   static Any IS_ACTOR_RIDING() { return invoke<Any>(0xA6BBE769); } // 0xA6BBE769
   static Any _0xF270EAC1(Any p0) { return invoke<Any>(0xF270EAC1, p0); } // 0xF270EAC1
   static BOOL IS_ACTOR_MOUNTED(Actor actor) { return invoke<BOOL>(0xA3AB3708, actor); } // 0xA3AB3708
   static Any GET_RIDER(Any p0) { return invoke<Any>(0x88A283E5, p0); } // 0x88A283E5
   static Actor GET_MOUNT(Actor actor) { return invoke<Actor>(0xDD31EC4E, actor); } // 0xDD31EC4E
   static void _ANIM_ANIMATOR_COMPONENT(Any p0, Any p1) { invoke<Void>(0xDC6DEE92, p0, p1); } // 0xDC6DEE92
   static Any ACTOR_MOUNT_ACTOR(Actor actor, Actor actor2) { return invoke<Any>(0xC28242F4, actor, actor2); } // 0xC28242F4
   static Any REMOVE_HORSE_ACCESSORY(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x374D047A, p0, p1, p2, p3, p4, p5); } // 0x374D047A
   static Any _UNKNOWN_HORSE_ACCESSORY(Any p0, Any p1) { return invoke<Any>(0x75D4E33F, p0, p1); } // 0x75D4E33F
   static Any _0x6C939AA7(Any p0, Any p1) { return invoke<Any>(0x6C939AA7, p0, p1); } // 0x6C939AA7
   static Any HORSE_ENABLE_AUTO_JUMP_FOR_AI_RIDERS(Any p0, Any p1) { return invoke<Any>(0x6B6E05A8, p0, p1); } // 0x6B6E05A8
   static Any HORSE_AUTO_JUMP_ENABLED_FOR_AI_RIDERS(Any p0, Any p1) { return invoke<Any>(0xCA7CB126, p0, p1); } // 0xCA7CB126
   static Any _0x28FCBDF2(Any p0) { return invoke<Any>(0x28FCBDF2, p0); } // 0x28FCBDF2
   static Any _0x5DE07F18(Any p0) { return invoke<Any>(0x5DE07F18, p0); } // 0x5DE07F18
   static Any HORSE_SET_CURR_FRESHNESS(Any p0, Any p1) { return invoke<Any>(0xF3976D70, p0, p1); } // 0xF3976D70
   static Any HORSE_GET_CURR_FRESHNESS(Any p0) { return invoke<Any>(0xB8665D8A, p0); } // 0xB8665D8A
   static Any HORSE_LOCK_FRESHNESS(Any p0) { return invoke<Any>(0x8754817D, p0); } // 0x8754817D
   static Any HORSE_UNLOCK_FRESHNESS(Any p0) { return invoke<Any>(0x6AFA044B, p0); } // 0x6AFA044B
   static void _CHEAT_INFINITE_HORSE_STAMINA(BOOL toggle) { invoke<Void>(0xB731EB45, toggle); } // 0xB731EB45
}

namespace MOVABLE
{
   static void STREAMING_IS_MOVABLE_NAV_MESH_RESIDENT(Any p0) { invoke<Void>(0x8A0D3339, p0); } // 0x8A0D3339
   static void STREAMING_REQUEST_MOVABLE_NAV_MESH(Any p0) { invoke<Void>(0x63334F63, p0); } // 0x63334F63
   static void STREAMING_UNREQUEST_MOVABLE_NAV_MESH(Any p0) { invoke<Void>(0xC329E1DB, p0); } // 0xC329E1DB
   static void SET_ACTOR_MOVABLE_NAV_MESH(Any p0) { invoke<Void>(0xECEE9E20, p0); } // 0xECEE9E20
}

namespace MOVIE
{
   static int _WORLD_MOVIE_PLAYER(Any p0) { return invoke<int>(0x92028B49, p0); } // 0x92028B49
   static int _0x69FC319E() { return invoke<int>(0x69FC319E); } // 0x69FC319E
   static int _0xD036DF91() { return invoke<int>(0xD036DF91); } // 0xD036DF91
}

namespace MOVIE2
{
   static int _SET_MOTIVE(Any p0, Any p1, float p2) { return invoke<int>(0x1BED8493, p0, p1, p2); } // 0x1BED8493
}

namespace MUSIC
{
   static int _0x2A3B1045(Any p0) { return invoke<int>(0x2A3B1045, p0); } // 0x2A3B1045
   static int _0x27A96719(const char* p0, const char* p1) { return invoke<int>(0x27A96719, p0, p1); } // 0x27A96719
   static int _0xC0556FB8(Any p0, Any p1) { return invoke<int>(0xC0556FB8, p0, p1); } // 0xC0556FB8
}

namespace NAV
{
   static Any CREATE_NAV_QUERY(Any p0, Any p1) { return invoke<Any>(0xE2F41226, p0, p1); } // 0xE2F41226
   static int NAV_QUERY_IS_DONE(Any p0) { return invoke<int>(0xE96D01E5, p0); } // 0xE96D01E5
   static int NAV_QUERY_CAN_PATH_TO_POINT(Any p0) { return invoke<int>(0x5A511344, p0); } // 0x5A511344
   static void NAV_QUERY_RECEIVE_CAN_PATH_TO_POINT(Any p0, Any p1) { invoke<Void>(0xAFA35FFA, p0, p1); } // 0xAFA35FFA
   static void NAV_QUERY_START_CAN_PATH_TO_POINT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x07A777D7, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x07A777D7
   static void NAV_QUERY_STOP(Any p0) { invoke<Void>(0x50290FB3, p0); } // 0x50290FB3
}

namespace NET
{
   static int* _0x6BCFE549(Any p0, float p1) { return invoke<int*>(0x6BCFE549, p0, p1); } // 0x6BCFE549
   static void _0x50E637D7() { invoke<Void>(0x50E637D7); } // 0x50E637D7 unused
   static void NET_LOG(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x48275716, p0, p2, p3, p4, p5, p6); } // 0x48275716
   static int _0xD164026F() { return invoke<int>(0xD164026F); } // 0xD164026F
   static int NET_ENABLE_MULTIPLAYER(Any p0) { return invoke<int>(0x9180FF1C, p0); } // 0x9180FF1C
   static int _0x84B0B5D6() { return invoke<int>(0x84B0B5D6); } // 0x84B0B5D6
   static BOOL NET_IS_IN_SESSION() { return invoke<BOOL>(0xCDAC0F0E); } // 0x8CA54980
   static BOOL NET_IS_ONLINE_AVAILABLE() { return invoke<BOOL>(0x5FF2BAE0); } // 0x5FF2BAE0
   static int _0x7AB722D8() { return invoke<int>(0x7AB722D8); } // 0x7AB722D8
   static int NET_GET_PLAYMODE() { return invoke<int>(0xBC4B6B74); } // 0xBC4B6B74
   static int _0x18EC9CF0(Any p0) { return invoke<int>(0x18EC9CF0, p0); } // 0x18EC9CF0
   static const char* _NET_IS_PLAYER_ONLINE_GAMESPY(const char* result, const char* p1, void* p2) { return invoke<const char*>(0x17D14553, result, p1, p2); } // 0x17D14553
   static BOOL NET_IS_SESSION_HOST() { return invoke<BOOL>(0xCDAC0F0E); } // 0xCDAC0F0E
   static BOOL NET_IS_SESSION_CLIENT(Any p0) { return invoke<BOOL>(0xFF65A07C, p0); } // 0xFF65A07C
   static void _0x75DD203B(Any p0) { invoke<Void>(0x75DD203B, p0); } // 0x75DD203B
   static Any NET_GET_NAT_TYPE() { return invoke<Any>(0x31700C0A); } // 0x31700C0A
   static BOOL NET_IS_BUSY() { return invoke<BOOL>(0x0678A865); } // 0x0678A865
   static void NET_GET_NET_TIME(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xFF8DA25D, p0, p1, p2, p3); } // 0xFF8DA25D
   static Any _0xB829A92D(Any p0) { return invoke<Any>(0xB829A92D, p0); } // 0xB829A92D
   static BOOL _0x71D989BD() { return invoke<BOOL>(0x71D989BD); } // 0x71D989BD
   static Any _SCLUBSTAT_EMPTYGAMER() { return invoke<Any>(0x95CDCE7A); } // 0x95CDCE7A
   static int* _0xAD85A378() { return invoke<int*>(0xAD85A378); } // 0xAD85A378
   static int* _0x72B03551() { return invoke<int*>(0x72B03551); } // 0x72B03551
   static int GET_SLOT_FOR_HOST() { return invoke<int>(0x860FCDBD); } // 0x860FCDBD
   static Any GET_NUM_PLAYERS() { return invoke<Any>(0x0F99A8BC); } // 0x0F99A8BC
   static int NET_START_NEW_SCRIPT(Any p0, Any p1) { return invoke<int>(0x84D6F8A7, p0, p1); } // 0x84D6F8A7
   static Any _NET_SCRIPT_MSG_SEND(int channelId, int headerSize, int* buffer, int count, bool pushToQueue) { return invoke<Any>(0x5E985228, channelId, headerSize, buffer, count, pushToQueue); } // 0x5E985228
   static int _0xE2163ECC(Any p0, Any p1, Any p2) { return invoke<int>(0xE2163ECC, p0, p1, p2); } // 0xE2163ECC
   static int _0xB13DD691(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xB13DD691, p0, p1, p2, p3); } // 0xB13DD691
   static int _0x9253CC79(Any p0, Any p1, Any p2) { return invoke<int>(0x9253CC79, p0, p1, p2); } // 0x9253CC79
   static int _0x4957E482(Any p0, Any p1, Any p2) { return invoke<int>(0x4957E482, p0, p1, p2); } // 0x4957E482
   static void REGISTER_HOST_BROADCAST_VARIABLES(Any p0, Any p1) { invoke<Void>(0xBEDD194D, p0, p1); } // 0xBEDD194D
   static void REGISTER_CLIENT_BROADCAST_VARIABLES(Any p0, Any p1) { invoke<Void>(0xF1732769, p0, p1); } // 0xF1732769
   static void UNREGISTER_HOST_BROADCAST_VARIABLES() { invoke<Void>(0x2707F082); } // 0x2707F082
   static void UNREGISTER_CLIENT_BROADCAST_VARIABLES() { invoke<Void>(0x0130DB5D); } // 0x0130DB5D
   static int _IS_CLIENT_DATA_VALID_FOR_SLOT(Any p0, Any p1) { return invoke<int>(0xF81E2097, p0, p1); } // 0xF81E2097
   static int _IS_CLIENT_DATA_VALID_FOR_SLOT_2(Any p0, Any p1) { return invoke<int>(0x64C2DD40, p0, p1); } // 0x64C2DD40
   static int _0xA80C6DE6(Any p0) { return invoke<int>(0xA80C6DE6, p0); } // 0xA80C6DE6
   static int NET_IS_OBJECT_LOCAL(Any p0) { return invoke<int>(0xD12C55A5, p0); } // 0xD12C55A5
   static Any NET_REQUEST_OBJECT(Any p0) { return invoke<Any>(0x68EC589D, p0); } // 0x68EC589D
   static int _0x47C5E353(Any p0, Any p1) { return invoke<int>(0x47C5E353, p0, p1); } // 0x47C5E353
   static int _0x3932B786(int result) { return invoke<int>(0x3932B786, result); } // 0x3932B786
   static int _0x138F38AC(Any p0) { return invoke<int>(0x138F38AC, p0); } // 0x138F38AC
   static int _0x3E509DF1(Any p0, Any p1) { return invoke<int>(0x3E509DF1, p0, p1); } // 0x3E509DF1
   static int _0x8C7E41E2(Any p0, Any p1) { return invoke<int>(0x8C7E41E2, p0, p1); } // 0x8C7E41E2
   static int _0x1306549E(Any p0, Any p1) { return invoke<int>(0x1306549E, p0, p1); } // 0x1306549E
   static int* _0x5C4CAE3A(Any p0) { return invoke<int*>(0x5C4CAE3A, p0); } // 0x5C4CAE3A
   static int _0x579C2014(Any p0) { return invoke<int>(0x579C2014, p0); } // 0x579C2014
   static void _NET_SET_EQUIP_TYPE(Any p0) { invoke<Void>(0x7837890B, p0); } // 0x7837890B
   static int _0xA6D794FE(int result, Any p1) { return invoke<int>(0xA6D794FE, result, p1); } // 0xA6D794FE
   static int _0x1C147E14(int result, Any p1) { return invoke<int>(0x1C147E14, result, p1); } // 0x1C147E14
   static int _0xCA6231C1(Any p0) { return invoke<int>(0xCA6231C1, p0); } // 0xCA6231C1
   static int _NET_ACTOR_OBJECT_ID(int result, Any p0) { return invoke<int>(0xC09B114B, result, p0); } // 0xC09B114B
   static int _NET_ACTOR_OBJECT_ID_2(int result, Any p0) { return invoke<int>(0x7284A71B, result, p0); }  // 0x7284A71B
   static int _0x7AB65B0C() { return invoke<int>(0x7AB65B0C); } // 0x7AB65B0C
   static Any AWARD_ACHIEVEMENT(Any p0) { return invoke<Any>(0xCAA24B1A, p0); } // 0xCAA24B1A
   static Any HAS_ACHIEVEMENT_BEEN_PASSED(Any p0) { return invoke<Any>(0x136A5BE9, p0); } // 0x136A5BE9
   static int _0xC792A9E0() { return invoke<int>(0xC792A9E0); } // 0xC792A9E0
   static Any AWARD_AVATAR(Any p0) { return invoke<Any>(0xDD33E221, p0); } // 0xDD33E221
   static Any NET_GET_POSSE_COUNT() { return invoke<Any>(0xC4F9DA6E); } // 0xC4F9DA6E
   static BOOL NET_IS_POSSE_LEADER() { return invoke<BOOL>(0x1CAD6D29); } // 0x1CAD6D29
   static int NET_GET_POSSE_LEADER_SLOT() { return invoke<int>(0x0D914C89); } // 0x0D914C89
   static int _0xFC52BD15(Any p0) { return invoke<int>(0xFC52BD15, p0); } // 0xFC52BD15
   static Any NET_GET_GAMER_POSSE_SIZE(Any p0) { return invoke<Any>(0xB6006EA9, p0); } // 0xB6006EA9
   static int _0x98A5CDC5(Any p0) { return invoke<int>(0x98A5CDC5, p0); } // 0x98A5CDC5
   static int _0x106CE441(Any p0) { return invoke<int>(0x106CE441, p0); } // 0x106CE441
   static int _0x6A7B9FAD(Any p0) { return invoke<int>(0x6A7B9FAD, p0); } // 0x6A7B9FAD
   static int _0x2037A74F(Any p0) { return invoke<int>(0x2037A74F, p0); } // 0x2037A74F
   static int _0x89D8FC30() { return invoke<int>(0x89D8FC30); } // 0x89D8FC30
   static BOOL _0x2010ABE6() { return invoke<BOOL>(0x2010ABE6); } // 0x2010ABE6
   static int _0xF6E40FF3(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0xF6E40FF3, p0, p1, p2, p3, p4); } // 0xF6E40FF3
   static int _0xC0849D70() { return invoke<int>(0xC0849D70); } // 0xC0849D70
   static int _0x8DF05A4F(Any p0) { return invoke<int>(0x8DF05A4F, p0); } // 0x8DF05A4F
   static Any NET_SESSION_LEAVE_SESSION() { return invoke<Any>(0x4AE5DBB2); } // 0x4AE5DBB2
   static BOOL NET_IS_FACTION_SAFE(Any p0) { return invoke<BOOL>(0x80B20614, p0); } // 0x80B20614
   static int NET_SESSION_START_GAMEPLAY() { return invoke<int>(0x86FF3A9B); } // 0x86FF3A9B
   static int NET_SESSION_END_GAMEPLAY() { return invoke<int>(0x81FD9851); } // 0x81FD9851
   static int NET_SESSION_SET_INVITABLE(Any p0) { return invoke<int>(0x3A5C56E3, p0); } // 0x3A5C56E3
   static int _0xFA0E1F8B(Any p0) { return invoke<int>(0xFA0E1F8B, p0); }  // 0xFA0E1F8B
   static int _0xCC7D0431(Any p0) { return invoke<int>(0xCC7D0431, p0); } // 0xCC7D0431
   static int NET_SESSION_IS_GAMEPLAY_STARTED() { return invoke<int>(0xDC88B308); } // 0xDC88B308
   static int _0xD923CD1B(Any p0, Any p1) { return invoke<int>(0xD923CD1B, p0, p1); } // 0xD923CD1B
   static int _NET_REQUEST_BECOME_GAME_HOST(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x7540959C, p0, p1, p2, p3); } // 0x7540959C
   static void NET_SET_THIS_SCRIPT_IS_NET_SCRIPT(Any p0) { invoke<Void>(0xEE3B79EE, p0); } // 0xEE3B79EE
   static int _0x4238C471() { return invoke<int>(0x4238C471); } // 0x4238C471
   static Any NET_GET_SCRIPT_STATUS() { return invoke<Any>(0x667DA125); } // 0x667DA125
   static BOOL NET_IS_PLAYER_PARTICIPANT(Player player) { return invoke<BOOL>(0x110A9B2F, player); } // 0x110A9B2F
   static BOOL NET_IS_HOST_OF_THIS_SCRIPT() { return invoke<BOOL>(0x6D403720); } // 0x6D403720
   static Any NET_GET_HOST_OF_THIS_SCRIPT() { return invoke<Any>(0x9272C3BA); } // 0x9272C3BA
   static int _0x408E28E2(Any p0) { return invoke<int>(0x408E28E2, p0); } // 0x408E28E2
   static int _0xC0FC4B57() { return invoke<int>(0xC0FC4B57); } // 0xC0FC4B57
   static int _0xD9965A9A() { return invoke<int>(0xD9965A9A); } // 0xD9965A9A
   static void SET_RICH_PRESENCE(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x7BDCBD45, p0, p1, p2, p3, p4); } // 0x7BDCBD45
   static void _0x50C18480(Any p0, Any p1) { invoke<Void>(0x50C18480, p0, p1); } // 0x50C18480
   static int _0xE5645CB3() { return invoke<int>(0xE5645CB3); } // 0xE5645CB3
   static int _0x79AFAB1F(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13, Any p14, Any p15, Any p16, Any p17, Any p18) { return invoke<int>(0x79AFAB1F, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18); } // 0x79AFAB1F
   static int _0x581CAC89() { return invoke<int>(0x581CAC89); } // 0x581CAC89
   static int _0xA174152C(Any p0) { return invoke<int>(0xA174152C, p0); } // 0xA174152C
   static int _0x0183A3F0(Any p0) { return invoke<int>(0x0183A3F0, p0); } // 0x0183A3F0
   static int _0x63034F52(Any p0) { return invoke<int>(0x63034F52, p0); } // 0x63034F52
   static int _0xE9EAC45C(Any p0) { return invoke<int>(0xE9EAC45C, p0); } // 0xE9EAC45C
   static int _0xBDF22FCA(Any p0) { return invoke<int>(0xBDF22FCA, p0); } // 0xBDF22FCA
   static int _0x9EA132A3(Any p0) { return invoke<int>(0x9EA132A3, p0); } // 0x9EA132A3
   static int NET_SESSION_SET_GAME_MODE_TYPE(Any p0) { return invoke<int>(0xCB0BCAE2, p0); } // 0xCB0BCAE2
   static int NET_VOICE_BROADCAST_ENABLE() { return invoke<int>(0x7A99E7DE); } // 0x7A99E7DE
   static int NET_VOICE_BROADCAST_DISABLE() { return invoke<int>(0x1D5E39A0); } // 0x1D5E39A0
   static int _0xEF6BF96E() { return invoke<int>(0xEF6BF96E); } // 0xEF6BF96E
   static Any NET_IS_UNLOCKED(Any p0) { return invoke<Any>(0xC8B680B3, p0); } // 0xC8B680B3
   static int NET_GET_OVERLOAD_STATE_FOR_SLOT(Any p0) { return invoke<int>(0xBE0E275F, p0); } // 0xBE0E275F
   static Any NET_GET_AREA_OVERLOAD_STATE_FOR_SLOT(Any p0) { return invoke<Any>(0xCB42389E, p0); } // 0xCB42389E
   static int _0x842ADE0A() { return invoke<int>(0x842ADE0A); } // 0x842ADE0A
   static int _0xB7856424() { return invoke<int>(0xB7856424); } // 0xB7856424
   static void UPDATE_PROFILE_STAT(Any p0, Any p1, Any p2) { invoke<Void>(0xF2FA1DE8, p0, p1, p2); } // 0xF2FA1DE8
   static int _0xCF674E31(Any p0, Any p1) { return invoke<int>(0xCF674E31, p0, p1); } // 0xCF674E31
   static int _AH_LAG_HACK_KILL_PROTECTION_ENABLE(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x97F15B69, p0, p1, p2, p3); } // 0x97F15B69
   static int _AH_LAG_HACK_MOVE_PROTECTION_ENABLE(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xCA0739A8, p0, p1, p2, p3); } // 0xCA0739A8
   static int _REMOTE_EXPLODE_TARGET(Actor actor) { return invoke<int>(0x49BC0219, actor); } // 0x49BC0219
   static int _0xD6780B56(Any p0, Any p1, Any p2) { return invoke<int>(0xD6780B56, p0, p1, p2); } // 0xD6780B56
   static int* _0x9A5841E5() { return invoke<int*>(0x9A5841E5); } // 0x9A5841E5
}

namespace NET2
{
   static int _0x55C5BB93(Any p0) { return invoke<int>(0x55C5BB93); } // 0x55C5BB93
   static int _0xFAD5A270(Any p0, Any p1) { return invoke<int>(0xFAD5A270, p0, p1); } // 0xFAD5A270
   static BOOL _0x4A721118(Any p0) { return invoke<BOOL>(0x4A721118, p0); } // 0x4A721118
   static int _0x4500B98A(Any p0) { return invoke<int>(0x4500B98A, p0); } // 0x4500B98A
   static int _0x85049505(Any p0, Any p1) { return invoke<int>(0x85049505, p0, p1); } // 0x85049505
   static int _0x5C51D43C(Any p0, Any p1) { return invoke<int>(0x5C51D43C, p0, p1); } // 0x5C51D43C
   static int _0x0E2C4B68(Any p0, Any p1) { return invoke<int>(0x0E2C4B68, p0, p1); } // 0x0E2C4B68
   static int _0xB514ECA7(Any p0, Any p1) { return invoke<int>(0xB514ECA7, p0, p1); }  // 0xB514ECA7
}

namespace NET3
{
   static void NET_UPDATE_LEADERBOARD(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x12304873, p0, p2, p3); } // 0x12304873
   static int _0x4D0C8AA4(Any p0) { return invoke<int>(0x4D0C8AA4, p0); } // 0x4D0C8AA4
   static int _0x89277EA3() { return invoke<int>(0x89277EA3); } // 0x89277EA3
   static int _0x2B8F86ED(Any p0) { return invoke<int>(0x2B8F86ED, p0); } // 0x2B8F86ED
   static int _0x88249424(Any p0, Any p1, Any p2) { return invoke<int>(0x88249424, p0, p1, p2); } // 0x88249424
   static int _0x87A3A38D(Any p0) { return invoke<int>(0x87A3A38D, p0); } // 0x87A3A38D
   static int _0xD7572C68(Any p0) { return invoke<int>(0xD7572C68, p0); } // 0xD7572C68
   static int _0x76F09F04() { return invoke<int>(0x76F09F04); } // 0x76F09F04
   static int _0xA684E813() { return invoke<int>(0xA684E813); } // 0xA684E813
   static int _0xE5C5CE63() { return invoke<int>(0xE5C5CE63); } // 0xE5C5CE63
   static int _0x4F652A00() { return invoke<int>(0x4F652A00); } // 0x4F652A00
   static int _0xFC564903() { return invoke<int>(0xFC564903); } // 0xFC564903
   static int _0x7154D15B() { return invoke<int>(0x7154D15B); }  // 0x7154D15B
   static int _0x86BC0A55(Any p0, Any p1) { return invoke<int>(0x86BC0A55, p0, p1); } // 0x86BC0A55
   static int _0xEB4A6D85() { return invoke<int>(0xEB4A6D85); } // 0xEB4A6D85
   static BOOL _0x5FD52711() { return invoke<int>(0x5FD52711); } // 0x5FD52711
   static BOOL _0xD0808C42() { return invoke<int>(0xD0808C42); } // 0xD0808C42
   static int _0x097BB984() { return invoke<int>(0x097BB984); } // 0x097BB984
   static int _0xEA7ADF42() { return invoke<int>(0xEA7ADF42); } // 0xEA7ADF42
   static int _0x3A8C77AD(Any p0) { return invoke<int>(0x3A8C77AD, p0); } // 0x3A8C77AD
   static int _0xE89C6E4F() { return invoke<int>(0xE89C6E4F); } // 0xE89C6E4F
   static int _0x0791F35A() { return invoke<int>(0x0791F35A); } // 0x0791F35A
   static int _0x49C2B05F(Any p0) { return invoke<int>(0x49C2B05F, p0); } // 0x49C2B05F
   static int _0xC813DBEF() { return invoke<int>(0xC813DBEF); } // 0xC813DBEF
   static int _0xE6B4F505() { return invoke<int>(0xE6B4F505); } // 0xE6B4F505
   static int _0x70AF0351(Any p0) { return invoke<int>(0x70AF0351); } // 0x70AF0351
   static int _0x293C3288() { return invoke<int>(0x293C3288); } // 0x293C3288
   static int _0xA7F231B0() { return invoke<int>(0xA7F231B0); } // 0xA7F231B0
   static int _0x984749B4(Any p0) { return invoke<int>(0x984749B4, p0); } // 0x984749B4
}

namespace NET4
{
   static int _0x8808546E() { return invoke<int>(0x8808546E); } // 0x8808546E
   static int _0x1A47001B() { return invoke<int>(0x1A47001B); } // 0x1A47001B
   static int _0x0FF6B8F4() { return invoke<int>(0x0FF6B8F4); } // 0x0FF6B8F4
   static int NET_GET_FREE_ROAM_MODE() { return invoke<int>(0x81F24788); } // 0x81F24788
   static void NET_SET_FREE_ROAM_MODE(int mode) { invoke<Void>(0x41921C98, mode); } // 0x41921C98
   static void NET_REGISTER_GAME_TYPE(Any p0, Any p1) { invoke<Void>(0xE822010A, p0, p1); } // 0xE822010A
   static void _0xA9459BB6(Any p0, Any p1, Any p2) { invoke<Void>(0xA9459BB6, p0, p1, p2); } // 0xA9459BB6
   static void _0x9D9784B8(Any p0, Any p1) { invoke<Void>(0x9D9784B8, p0, p1); } // 0x9D9784B8
   static int _0x03962973() { return invoke<int>(0x03962973); } // 0x03962973
   static int _0x8E0D7219(Any p0, Any p1) { return invoke<int>(0x8E0D7219, p0, p1); } // 0x8E0D7219
   static int _0xC00C8C94(Any p0) { return invoke<int>(0xC00C8C94, p0); } // 0xC00C8C94
   static int _0x9BC05C90(Any p0, Any p1) { return invoke<int>(0x9BC05C90, p0, p1); }  // 0x9BC05C90
   static int NET_GET_GAMER_RGB_COLOR(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x97931B87, p0, p1, p2, p3); } // 0x97931B87
   static int _0xFE83A4FE(Any p0) { return invoke<int>(0xFE83A4FE, p0); } // 0xFE83A4FE
   static int _0x8DEC3E03(Any p0) { return invoke<int>(0x8DEC3E03, p0); } // 0x8DEC3E03
   static int _0xBECB3EEC(Any p0, Any p1, Any p2, float p3) { return invoke<int>(0xBECB3EEC, p0, p1, p2, p3); } // 0xBECB3EEC
   static BOOL _0x75F27D60(Any p0) { return invoke<BOOL>(0x75F27D60, p0); } // 0x75F27D60
   static int NET_PLAYER_SHOW_CONTEXT_MENU(Any p0, Any p1) { return invoke<int>(0xA64A451E, p0, p1); } // 0xA64A451E
   static int NET_PLAYER_LIST_RESET() { return invoke<int>(0x67031EDA); } // 0x67031EDA
   static BOOL NET_PLAYER_LIST_ADD_ITEM(const char* text, int rowIndex) { return invoke<BOOL>(0xFD355ED1, text, rowIndex); } // 0xFD355ED1
   static int _0x805AC16A(Any p0, Any p1) { return invoke<int>(0x805AC16A, p0, p1); } // 0x805AC16A
   static int NET_PLAYER_LIST_SET_HIGHLIGHT(int highlightIndex) { return invoke<int>(0x0AAE9E6B, highlightIndex); } // 0x0AAE9E6B
   static int NET_PLAYER_LIST_SET_TOP_TEAM(Any p0) { return invoke<int>(0x20B684AB, p0); } // 0x20B684AB
   static int NET_PLAYER_LIST_SET_TEAM_SCORE(Any p0, Any p1, Any p2) { return invoke<int>(0x84CD0651, p0, p1, p2); } // 0x84CD0651
   static int NET_PLAYER_LIST_SET_TEAM_SORT(Any p0) { return invoke<int>(0xA56B459C, p0); } // 0xA56B459C
   static int NET_PLAYER_LIST_SET_TITLE(const char* gxtName) { return invoke<int>(0x0547A660, gxtName); } // 0x0547A660
   static int NET_PLAYER_LIST_SET_TEMPLATE(int menuTemplate) { return invoke<int>(0xD6111569, menuTemplate); } // 0xD6111569
   static int NET_PLAYER_LIST_SET_HEADER(int columnIndex, const char* entry) { return invoke<int>(0xFA382FCB, columnIndex, entry); } // 0xFA382FCB
   static int NET_PLAYER_LIST_SET_DESCRIPTION(const char* str) { return invoke<int>(0xCF065186, str); } // 0xCF065186
   static int _0xBE7965C8(Any p0) { return invoke<int>(0xBE7965C8, p0); } // 0xBE7965C8
   static int _0xD4C7E0D5(Any p0) { return invoke<int>(0xD4C7E0D5, p0); } // 0xD4C7E0D5
   static int NET_PLAYER_LIST_SET_CURRENT_ITEM() { return invoke<int>(0x98FC68AF); } // 0x98FC68AF
   static int _0x95A543E2(Any p0) { return invoke<int>(0x95A543E2, p0); } // 0x95A543E2
   static int _NET_PLAYER_LIST_SET_RIGHT_TEXT(int columnIndex, const char* text) { return invoke<int>(0xC673362C, columnIndex, text); } // 0xC673362C
   static int _0xEC6F465F(Any p0, Any p1) { return invoke<int>(0xEC6F465F, p0, p1); } // 0xEC6F465F
   static int _NET_PLAYER_LIST_SET_ITEM_COLOR(int groupColor) { return invoke<int>(0x794F5C21, groupColor); } // 0x794F5C21
   static int NET_PLAYER_LIST_SET_CURRENT_ITEM_PRIORITY(Any p0) { return invoke<int>(0xBD42097A, p0); } // 0xBD42097A
   static int _0xC09ACD5C(Any p0) { return invoke<int>(0xC09ACD5C, p0); } // 0xC09ACD5C
   static int _PRINT_CHAT(const char* text1, const char* text2, const char* text3, Any p3, Any p4, Any p5, Any p6) { return invoke<int>(0xC73DAD2B, text1, text2, text3, p3, p4, p5, p6); } // 0xC73DAD2B //MP_Ticker
   static int _0x8A1D83F2() { return invoke<int>(0x8A1D83F2); } // 0x8A1D83F2 //MP_Ticker
   static int _0xA6403262(Any p0, Any p1) { return invoke<int>(0xA6403262, p0, p1); } // 0xA6403262 XpCounter
   static int _0x27D40FD1(Any p0, Any p1, Any p2) { return invoke<int>(0x27D40FD1, p0, p1, p2); } // 0x27D40FD1 //ScoreGraph
   static int _0xA3AE09EF() { return invoke<int>(0xA3AE09EF); } // 0xA3AE09EF //ScoreGraph
   static int _0x746897AB(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x746897AB, p0, p1, p2, p3); } // 0x746897AB //ScoreGraph
   static int _0xB4C867BD() { return invoke<int>(0xB4C867BD); } // 0xB4C867BD //ScoreGraph
   static int _0x12558DBD(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x12558DBD, p0, p1, p2, p3); } // 0x12558DBD //ScoreGraph
   static int _0x134AAF17(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x134AAF17, p0, p1, p2, p3); } // 0x134AAF17 //ScoreGraph
}

namespace NETCONNECTION
{
   static int _0x2547029C(Any p0, Any p1) { return invoke<int>(0x2547029C, p0, p1); } // 0x2547029C
   static Any _0x6F6D942B(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<Any>(0x6F6D942B, p0, p1, p2, p3, p4, p5, p6); } // 0x6F6D942B
   static Any _0x713B1D7F(Any p0, Any p1) { return invoke<Any>(0x713B1D7F, p0, p1); } // 0x713B1D7F
   static Any _START(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x9C80A3A4, p0, p1, p2, p3, p4); } // 0x9C80A3A4
   static Any _MP_DEED_START(Any p0) { return invoke<Any>(0x27A00456, p0); } // 0x27A00456
   static Any _MP_DEED_COMPLETE(Any p0) { return invoke<Any>(0x120E6123, p0); } // 0x120E6123
   static Any _MP_DEED_COMPLETE_EX(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x4585821E, p0, p1, p2, p3); }// 0x4585821E
   static Any _MP_COOP_COMPLETE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0x46C39437, p0, p1, p2, p3, p4, p5); } // 0x46C39437
}

namespace PATH
{
   static int _0x44930268(Any p0, Any p1) { return invoke<int>(0x44930268, p0, p1); } // 0x44930268
   static int _0xECC40138(Any p0, float p1, float p2, float p3) { return invoke<int>(0xECC40138, p0, p1, p2, p3); } // 0xECC40138
   static int _0xCD89FB70(Any p0, Any p1, float p2, float p3, float p4) { return invoke<int>(0xCD89FB70, p0, p1, p2, p3, p4); } // 0xCD89FB70
   static int _0xBD374C00(Any p0) { return invoke<int>(0xBD374C00, p0); } // 0xBD374C00
   static int _0x42A4CCD5(Any p0) { return invoke<int>(0x42A4CCD5, p0); } // 0x42A4CCD5
   static void GET_PATH_POINT(Any p0, Any p1, Any p2) { invoke<Void>(0x415F635C, p0, p1, p2); } // 0x415F635C
   static float ESTIMATE_PATH_LENGTH(Any p0) { return invoke<float>(0x2B02A877, p0); } // 0x2B02A877
   static int ESTIMATE_DISTANCE_ALONG_PATH(Any p0, Any p1, Any p2, float p3, Any p4) { return invoke<int>(0x7A00433F, p0, p1, p2, p3, p4); } // 0x7A00433F
   static void ESTIMATE_TWO_DISTANCES_ALONG_PATH(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xA1D9AF6B, p0, p1, p2, p3, p4, p5); } // 0xA1D9AF6B
}

namespace PERSCHAR
{
   static Any ACTIVATE_ACTOR_FOR_PERS_CHAR(Any p0) { return invoke<Any>(0x2CA16327, p0); } // 0x2CA16327
   static Any DEACTIVATE_ACTOR_FOR_PERS_CHAR(Any p0) { return invoke<Any>(0x9B2A39BC, p0); } // 0x9B2A39BC
   static void DEACTIVATE_ACTORS_FOR_PERS_CHARS_IN_VOLUME(Any p0) { invoke<Void>(0x6F8C238B, p0); } // 0x6F8C238B
   static Any GET_ACTOR_FROM_PERS_CHAR(Any p0) { return invoke<Any>(0xE04ED21E, p0); } // 0xE04ED21E
   static Any GET_PERS_CHAR_DEATH_TIMESTAMP(Any p0) { return invoke<Any>(0xD78D1B4F, p0); } // 0xD78D1B4F
   static Any GET_PERS_CHAR_FROM_ACTOR(Any p0) { return invoke<Any>(0x69DA275F, p0); } // 0x69DA275F
   static Any SET_PERS_CHAR_SAFE_ZONE(Any p0, Any p1) { return invoke<Any>(0x67258116, p0, p1); } // 0x67258116
   static BOOL IS_PERS_CHAR_ALIVE(Any p0) { return invoke<BOOL>(0x5F3A1B81, p0); } // 0x5F3A1B81
   static Any REVIVE_PERS_CHAR(Any p0, Any p1) { return invoke<Any>(0xEDA4B02B, p0, p1); } // 0xEDA4B02B
   static void SET_PERS_CHAR_EXEMPT_FROM_AMBIENT_RESTRICTIONS(Any p0, Any p1) { invoke<Void>(0x2A709F33, p0, p1); } // 0x2A709F33
   static void SET_PERS_CHAR_ENABLED(Any p0, Any p1) { invoke<Void>(0xC85CFEA9, p0, p1); } // 0xC85CFEA9
   static void SET_PERS_CHAR_ALLOW_SPAWN_ELSEWHERE(Any p0, Any p1) { invoke<Void>(0x366B0AD1, p0, p1); } // 0x366B0AD1
}

namespace PHYSINST
{
   static BOOL IS_PROP_BROKEN(Any p0) { return invoke<BOOL>(0x25277BBC, p0); } // 0x25277BBC
   static Any GET_PROP_VELOCITY(Any p0, Any p1) { return invoke<Any>(0x5AEA8801, p0, p1); } // 0x5AEA8801
   static int SET_PROP_VELOCITY(Any p0, Any p1) { return invoke<int>(0x28425D8C, p0, p1); } // 0x28425D8C
   static int _0x544BCE48(Any p0, Any p1) { return invoke<int>(0x544BCE48, p0, p1); } // 0x544BCE48
   static int SET_PROP_VELOCITY_ON_AXIS(Any p0, Any p1, Any p2) { return invoke<int>(0xC9F3981D, p0, p1, p2); } // 0xC9F3981D
   static Any IS_PHYSINST_VALID(Any p0) { return invoke<Any>(0x16C0A6CB, p0); } // 0x16C0A6CB
   static BOOL IS_PHYSINST_READY(Any p0) { return invoke<BOOL>(0xE83E6A41, p0); } // 0xE83E6A41
   static BOOL IS_PHYSINST_IN_LEVEL(Any p0) { return invoke<BOOL>(0x6243A6AF, p0); } // 0x6243A6AF
   static void SET_SLEEP_TOLERANCE(Any p0, Any p1) { invoke<Void>(0x750ADBE5, p0, p1); } // 0x750ADBE5
   static void SET_BRIDGE_STIFFNESS(Any p0, Any p1) { invoke<Void>(0x987FD4F6, p0, p1); } // 0x987FD4F6
   static void ACTIVATE_PHYSINST(Any p0) { invoke<Void>(0xC0961D18, p0); } // 0xC0961D18
   static int _0x65CA3037(Any p0) { return invoke<int>(0x65CA3037, p0); } // 0x65CA3037
   static int _0x734CC17B(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0x734CC17B, p0, p1, p2, p3, p4, p5); } // 0x734CC17B
   static int _0x4FF36FA7(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0x4FF36FA7, p0, p1, p2, p3, p4, p5); }  // 0x4FF36FA7
   static int _0xC5E372BC(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xC5E372BC, p0, p1, p2, p3); } // 0xC5E372BC
   static int ATTACH_PHYSINST_TO_WORLD2(Any p0, Any p1, Any p2, Any p3, Any p4, float p5) { return invoke<int>(0x441CDD55, p0, p1, p2, p3, p4, p5); } // 0x441CDD55
   static int _0x4A05AA7D(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x4A05AA7D, p0, p1, p2, p3, p4); } // 0x4A05AA7D
   static void RELEASE_CONSTRAINT(Any p0) { invoke<Void>(0x8B9659EF, p0); } // 0x8B9659EF
   static void HIDE_PHYSINST(Any p0) { invoke<Void>(0x0D6BFDD9, p0); } // 0x0D6BFDD9
   static void SHOW_PHYSINST(Any p0) { invoke<Void>(0x342FDCD6, p0); } // 0x342FDCD6
   static void SET_SECTOR_PROPS_SUPER_LOCKED(Any p0, Any p1) { invoke<Void>(0xED3ADF67, p0, p1); } // 0xED3ADF67
   static void LIGHTS_SET_ON_TIME(Any p0, Any p1) { invoke<Void>(0x3774465F, p0, p1); } // 0x3774465F
   static void LIGHTS_SET_OFF_TIME(Any p0, Any p1) { invoke<Void>(0x3774465F, p0, p1); } // 0xD0CDEED4
   static int SET_PROP_NO_FADE(Any p0) { return invoke<int>(0x1260ACCC, p0); } // 0x1260ACCC
}

namespace PHYSINST2
{
   static int CREATE_OBJECT_LOCATOR(Any p0, Any p1) { return invoke<int>(0x11069324, p0, p1); } // 0x11069324
   static int _0x0B24362F(Any p0, Any p1, Any p2, float p3, float p4, float p5, float p6, float p7, float p8) { return invoke<int>(0x0B24362F, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x0B24362F
   static int _0xE25F407D(Any p0, Any p1, Any p2, float p3, float p4, float p5, float p6, float p7, float p8) { return invoke<int>(0xE25F407D, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xE25F407D
   static int _0xEB33480A(Any p0, Any p1, float p2, float p3, float p4, float p5, float p6, float p7) { return invoke<int>(0xEB33480A, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xEB33480A
   static int _0x88F7432C(Any p0, Any p1) { return invoke<int>(0x88F7432C, p0, p1); } // 0x88F7432C
   static int _0x04507DBC(Any p0, Any p1) { return invoke<int>(0x04507DBC, p0, p1); } // 0x04507DBC
}

namespace PLAYER
{
   static void TELEPORT_ACTOR(Actor actor, float x, float y, float z, BOOL p4, BOOL p5, BOOL p6) { invoke<Void>(0x2D54B916, actor, x, y, z, p4, p5, p6); } // 0x2D54B916
   static void TELEPORT_ACTOR_WITH_HEADING(Actor actor, float x, float y, float z, float heading, BOOL p5, BOOL p6, BOOL p7) { invoke<Void>(0xE4DE507C, actor, x, y, z, heading, p5, p6, p7); } // 0xE4DE507C
   static Any GET_MAX_SPEED(Any p0) { return invoke<Any>(0x6B3A39A9, p0); } // 0x6B3A39A9
   static void GET_POSITION(Actor actor, float* x, float* y, float* z) { invoke<Void>(0x99BD9D6F, actor, x, y, z); } // 0x99BD9D6F
   static float GET_HEADING(Actor actor) { return invoke<float>(0x42DE39F0, actor); } // 0x42DE39F0
   static Any GET_ACTOR_AXIS(Actor actor, Any p1, Any p2) { return invoke<Any>(0x294A5549, actor, p1, p2); } // 0x294A5549
   static void SET_ACTOR_HEADING(Actor actor, float heading, BOOL p2) { invoke<Void>(0xECE8520B, actor, heading, p2); } // 0xECE8520B
   static void SET_ACTOR_ONE_SHOT_DEATH(Actor actor, BOOL toggle) { invoke<Void>(0xCDC686B2, actor, toggle); } // 0xCDC686B2
   static int _SET_ACTOR_ONE_SHOT_DEATH(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<int>(0x0912622D, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x0912622D
   static int _0x758F993A(int* p0, Any p1) { return invoke<int>(0x758F993A, p0, p1); } // 0x758F993A
   static int _0x1AA3A0C0(Any p0, Any p1) { return invoke<int>(0x1AA3A0C0, p0, p1); } // 0x1AA3A0C0
   static BOOL IS_ACTOR_PLAYER(Actor actor) { return invoke<BOOL>(0xB27E91E7, actor); } // 0xB27E91E7
   static BOOL IS_ACTOR_LOCAL_PLAYER(Actor actor) { return invoke<BOOL>(0x6542CF26, actor); } // 0x6542CF26
   static int _PUSH_NEG_ONE() { return invoke<int>(0xB114332D); } // 0xB114332D
   static int _GET_ACTOR_CONTROLLER(Actor actor) { return invoke<int>(0x524F6981, actor); } // 0x524F6981
   static int _0xCF02D1D6() { return invoke<int>(0xCF02D1D6); } // 0xCF02D1D6
   static int _0x8F82B7D4(Any p0, Any p1) { return invoke<int>(0x8F82B7D4, p0, p1); } // 0x8F82B7D4
   static int _0xC733BC9A(Any p0, Any p1) { return invoke<int>(0xC733BC9A, p0, p1); } // 0xC733BC9A
   static void SET_PLAYER_CONTROL(Actor actor, BOOL toggle, int possiblyFlags, BOOL p3) { invoke<Void>(0xD17AFCD8, actor, toggle, possiblyFlags, p3); } // 0xD17AFCD8
   static void SET_PLAYER_ENABLE_MOUNT_USE_CONTEXTS(Actor actor, BOOL toggle) { invoke<Void>(0xBEEDDD54, actor, toggle); } // 0xBEEDDD54
   static void SET_PLAYER_ALLOW_PICKUP(Actor actor) { invoke<Void>(0xEA08A934, actor); } // 0xEA08A934
   static void SET_PLAYER_MELEE_MODE_SELECTED(Actor actor, int mode) { invoke<Void>(0xAC1285A3, actor, mode); } // 0xAC1285A3
   static void SET_PLAYER_DISABLE_TARGETING(Actor actor, Any p1) { invoke<Void>(0x0959C27A, actor, p1); } // 0x0959C27A
   static int _0x9613C2D0() { return invoke<int>(0x9613C2D0); } // 0x9613C2D0
   static BOOL IS_PLAYER_IN_COMBAT(Any p0) { return invoke<BOOL>(0x6576AD43, p0); } // 0x6576AD43
   static BOOL _0x48B7C279(float p0) { return invoke<BOOL>(0x48B7C279, p0); } // 0x48B7C279
   static int _0xCE7CE46D(Any p0, Any p1) { return invoke<int>(0xCE7CE46D, p0, p1); } // 0xCE7CE46D
   static void SET_PLAYER_CONTROL_RUMBLE(Player player, Any p1) { invoke<Void>(0x4590CE00, player, p1); } // 0x4590CE00
   static void RESET_RUMBLE() { invoke<Void>(0xB3BE2F95); } // 0xB3BE2F95
   static Any GET_PLAYER_CONTROL_CONFIG(Player player) { return invoke<Any>(0x8421033D, player); } // 0x8421033D
   static void SET_PLAYER_CONTROL_CONFIG(Player player, Any p1) { invoke<Void>(0x01B84BCA, player, p1); } // 0x01B84BCA
   static void PLAYER_RUMBLE(Any p0, Any p1, Any p2) { invoke<Void>(0x2E0EC2F2, p0, p1, p2); } // 0x2E0EC2F2
   static int _0x4B0D6152(float p0) { return invoke<int>(0x4B0D6152, p0); } // 0x4B0D6152
   static int _0x4D918005(float p0) { return invoke<int>(0x4D918005, p0); } // 0x4D918005
   static void SET_PLAYER_COMBATMODE(Player player, Any p1) { invoke<Void>(0x57595189, player, p1); } // 0x57595189
   static int GET_PLAYER_COMBATMODE() { return invoke<int>(0x86E193B8); } // 0x86E193B8
   static void SET_PLAYER_COMBATMODE_OVERRIDE(Player player, Any p1) { invoke<Void>(0xAFFBBE78, player, p1); } // 0xAFFBBE78
   static int _SET_COMBAT_MODE_OVERRIDE(Any p0) { return invoke<int>(0x1184EC7B, p0); } // 0x1184EC7B
   static void SET_PLAYER_VEHICLE_INPUT(Player player, Any p1, Any p2, Any p3) { invoke<Void>(0xE1160B04, player, p1, p2, p3); } // 0xE1160B04
   static int _0x900165CE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<int>(0x900165CE, p0, p1, p2, p3, p4, p5, p6); } // 0x900165CE
   static int _0xBFC8EF7C(Any p0, Any p1) { return invoke<int>(0xBFC8EF7C, p0, p1); } // 0xBFC8EF7C
   static void CLEAR_PLAYER_CONTROL_HORSE_FOLLOW(Any p0, Any p1) { invoke<Void>(0x7C522386, p0, p1); } // 0x7C522386
   static BOOL IS_PLAYER_IN_HORSE_FOLLOW(Player player, Any p1) { return invoke<BOOL>(0xE44DCE87, player, p1); } // 0xE44DCE87
   static Actor GET_PLAYER_ACTOR(Player player) { return invoke<Actor>(0xE8CFDD53, player); } // 0xE8CFDD53
   static BOOL IS_LOCAL_PLAYER(Any p0) { return invoke<BOOL>(0x40EF1003, p0); } // 0x40EF1003
   static BOOL IS_LOCAL_PLAYER_VALID(Actor actor) { return invoke<BOOL>(0x0ADC17E9, actor); } // 0x0ADC17E9
   static BOOL IS_SLOT_VALID(int slot) { return invoke<BOOL>(0xD04480FE, slot); } // 0xD04480FE
   static Any GET_SLOT_ACTOR(Any p0) { return invoke<Any>(0xDB9B49D8, p0); } // 0xDB9B49D8
   static int GET_ACTOR_SLOT(Actor actor) { return invoke<int>(0xAABF3356, actor); } // 0xAABF3356
   static int GET_LOCAL_SLOT() { return invoke<int>(0xAD68A22E); } // 0xAD68A22E
   static const char* GET_SLOT_NAME(int slot) { return invoke<const char*>(0x34CBABAE, slot); } // 0x34CBABAE
   static Any GET_SLOT_POSITION(int slot, float* x, float* y, float* z) { return invoke<Any>(0x3241158C, slot, x, y, z); } // 0x3241158C
   static int GET_SLOT_FACING(Any p0, Any p1) { return invoke<int>(0x34A9866B, p0, p1); } // 0x34A9866B
   static BOOL IS_PLAYER_TARGETTING_ACTOR(Any p0, Any p1, Any p2) { return invoke<BOOL>(0x87DDCA96, p0, p1, p2); } // 0x87DDCA96
   static BOOL IS_PLAYER_TARGETTING_OBJECT(Any p0, Any p1) { return invoke<BOOL>(0x622796D5, p0, p1); } // 0x622796D5
   static BOOL IS_PLAYER_DEADEYE(Any p0) { return invoke<BOOL>(0x6148423A, p0); } // 0x6148423A
   static void SET_PLAYER_DEADEYE_MODE(Any p0, Any p1) { invoke<Void>(0xB6A47C37, p0, p1); } // 0xB6A47C37
   static void SET_FORCE_PLAYER_AIM_MODE(Any p0, Any p1) { invoke<Void>(0x1CFAF2EA, p0, p1); } // 0x1CFAF2EA
   static void SET_PLAYER_ENDLESS_READYMODE(Any p0, Any p1) { invoke<Void>(0xD0E08B5E, p0, p1); } // 0xD0E08B5E
   static int GET_PLAYER_ZOOM_STATE(Any p0) { return invoke<int>(0xBC521A38, p0); } // 0xBC521A38
   static BOOL IS_PLAYER_USING_COVER(Any p0) { return invoke<BOOL>(0x724A2931, p0); } // 0x724A2931
   static void ATTACH_PLAYER_TO_COVER(Any p0, Any p1, Any p2) { invoke<Void>(0x45F2A70A, p0, p1, p2); } // 0x45F2A70A
   static void SIMULATE_PLAYER_INPUT_GAIT(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x0D77CC34, p0, p1, p2, p3); } // 0x0D77CC34
   static void ACTOR_POP_NEXT_GAIT(Any p0, Any p1, Any p2) { invoke<Void>(0xEAE75C6F, p0, p1, p2); } // 0xEAE75C6F
   static int ACTOR_SET_MAX_GAIT(Any p0, Any p1) { return invoke<int>(0x1ABFBFA3, p0, p1); } // 0x1ABFBFA3
   static BOOL IS_ACTOR_USING_COVER(Any p0) { return invoke<BOOL>(0xD39C4A9E, p0); } // 0xD39C4A9E
   static BOOL IS_ACTOR_USING_LEDGE(Any p0) { return invoke<BOOL>(0xEBBE1CAC, p0); } // 0xEBBE1CAC
   static void SET_PLAYER_DEADEYE_POINTS(Any p0, Any p1, Any p2) { invoke<Void>(0x50D8C840, p0, p1, p2); } // 0x50D8C840
   static void ADD_PLAYER_DEADEYE_POINTS(Any p0, Any p1, Any p2) { invoke<Void>(0xE2C4AEE7, p0, p1, p2); } // 0xE2C4AEE7
   static int GET_PLAYER_DEADEYE_POINTS(Any p0) { return invoke<int>(0x86B5C9E1, p0); } // 0x86B5C9E1
   static void SET_DISABLE_DEADEYE(Any p0, Any p1) { invoke<Void>(0x09716951, p0, p1); } // 0x09716951
   static void SET_DEADEYE_POINT_MODIFIER(Any p0, Any p1) { invoke<Void>(0x0486955B, p0, p1); } // 0x0486955B
   static void SET_MAX_DEADEYE_POINTS(Any p0, Any p1) { invoke<Void>(0x526D45B7, p0, p1); } // 0x526D45B7
   static void SET_DEADEYE_MULTILOCK_ENABLE(Any p0, Any p1) { invoke<Void>(0x4E6E5E78, p0, p1); } // 0x4E6E5E78
   static void SET_DEADEYE_TARGETPAINT_ENABLE(Any p0, Any p1) { invoke<Void>(0x5CD6E2C3, p0, p1); } // 0x5CD6E2C3
   static void SET_DEADEYE_INVULNERABILITY(Any p0, Any p1) { invoke<Void>(0xA671FF8E, p0, p1); } // 0xA671FF8E
   static void SET_DEADEYE_DAMAGE_SCALING(Any p0, float p1) { invoke<Void>(0x0D583DAF, p0, p1); } // 0x0D583DAF
   static int SET_DEADEYE_TIME_LIMIT(Any p0, float p1) { return invoke<int>(0x863F0193, p0, p1); } // 0x863F0193
   static void SET_DEADEYE_REGENERATION_RATE(Actor actor, float rate, Any p2) { invoke<Void>(0x0415EE4C, actor, rate, p2); } // 0x0415EE4C
   static void SET_DEADEYE_REGENERATION_RATE_MULTIPLIER(Any p0, Any p1) { invoke<Void>(0x151741A2, p0, p1); } // 0x151741A2
   static void SET_DEADEYE_TIMESCALE(Any p0, float p1) { invoke<Void>(0x5740CDC2, p0, p1); } // 0x5740CDC2
   static void SET_INFINITE_DEADEYE(Any p0, BOOL toggle) { invoke<Void>(0x0C0BC04E, p0, toggle); } // 0x0C0BC04E
   static float _0x7F454A92(Any p0) { return invoke<float>(0x7F454A92, p0); } // 0x7F454A92
   static int SET_WAGON_TO_WAGON_JACK_ENABLE(Any p0, Any p1) { return invoke<int>(0xFA8D2B69, p0, p1); } // 0xFA8D2B69
   static void SET_PLAYER_POSTURE(Any p0, Any p1, Any p2) { invoke<Void>(0x3BD4426B, p0, p1, p2); } // 0x3BD4426B
   static void SET_ACTOR_ALLOW_DISMOUNT(Actor p0, Any p1) { invoke<Void>(0xC550644A, p0, p1); } // 0xC550644A
   static void SET_ACTOR_INVULNERABILITY(Actor actor, BOOL toggle) { invoke<Void>(0xE38EF526, actor, toggle); } // 0xE38EF526
   static BOOL GET_ACTOR_INVULNERABILITY(Actor actor) { return invoke<BOOL>(0xDB39D992, actor); } // 0xDB39D992
   static void SET_TOUGH_ACTOR(Actor actor, BOOL toggle) { invoke<Void>(0x2A575132, actor, toggle); } // 0x2A575132
   static void SET_ACTOR_UNKILLABLE(Actor actor, BOOL toggle) { invoke<Void>(0x0D9A35F6, actor, toggle); } // 0x0D9A35F6
   static int SET_ACTOR_PERMANENT(Any p0) { return invoke<int>(0xB4CD475D, p0); } // 0xB4CD475D
   static int _SET_ACTOR_PERMANENT_2(Any p0) { return invoke<int>(0x731F2C21, p0); } // 0x731F2C21
   static int SET_ACTOR_FROZEN_AFTER_CORPSIFY(Any p0) { return invoke<int>(0xED89D0E0, p0); } // 0xED89D0E0
   static void CLEAR_ACTOR_PROOF(Any p0, Any p1) { invoke<Void>(0xF5B74E20, p0, p1); } // 0xF5B74E20
   static int CLEAR_ACTOR_PROOF_ALL(int result, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x9E7AE28B, result, p1, p2, p3, p4); } // 0x9E7AE28B
   static int GET_ACTOR_PROOF(Any p0) { return invoke<int>(0x147EA072, p0); } // 0x147EA072
   static void SET_ACTOR_PROOF(Any p0, Any p1) { invoke<Void>(0xA5875DC8, p0, p1); } // 0xA5875DC8
   static int _SET_ACTOR_OVER_HEALTH_MODE(Any p0) { return invoke<int>(0xF2F77F44, p0); } // 0xF2F77F44
   static int _REPAIR_INCAPACITATION(Any p0) { return invoke<int>(0x437588E6, p0); } // 0x437588E6
   static int GET_ACTOR_INCAPACITATED(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xEE4E2461, p0, p1, p2, p3); } // 0xEE4E2461
   static void SET_ALLOW_RIDE_BY_AI(Any p0, Any p1) { invoke<Void>(0x2D9C0C0F, p0, p1); }// 0x2D9C0C0F
   static int GET_ALLOW_RIDE_BY_PLAYER(Any p0) { return invoke<int>(0x0318FF2A, p0); } // 0x0318FF2A
   static void SET_ALLOW_RIDE_BY_PLAYER(Actor actor, BOOL p0) { invoke<Void>(0xCF1A1BC5, actor, p0); }// 0xCF1A1BC5
   static int SET_ALLOW_RIDE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0xF83A8D2B, p0, p1, p2, p3, p4, p5); } // 0xF83A8D2B
   static BOOL GET_ALLOW_RIDE(Any p0) { return invoke<BOOL>(0x0111E8E0, p0); } // 0x0111E8E0
   static void SET_ALLOW_JACK(Any p0, Any p1) { invoke<Void>(0x5D5BD1F0, p0, p1); } // 0x5D5BD1F0
   static void SET_ALLOW_EXECUTE(Any p0, Any p1) { invoke<Void>(0x5896817B, p0, p1); } // 0x5896817B
   static void SET_ALLOW_DEADEYE_LOCKS(Any p0, Any p1) { invoke<Void>(0xA1BFC1A5, p0, p1); } // 0xA1BFC1A5
   static void SET_DEADEYE_LOCKS_ON_HEAD_ONLY(Any p0, Any p1) { invoke<Void>(0x9375946B, p0, p1); } // 0x9375946B
   static int SET_ALLOW_MELEE_SPECIAL_MOVE(Any p0, Any p1) { return invoke<int>(0x740B78A8, p0, p1); } // 0x740B78A8
   static int SET_ALLOW_LASSO_MINI_GAME(Any p0, Any p1) { return invoke<int>(0x7A11D611, p0, p1); } // 0x7A11D611
   static void ACTOR_DISMOUNT_NOW(Any p0) { invoke<Void>(0x0666B436, p0); } // 0x0666B436
   static BOOL _0xBFD6AE3D(Any p0) { return invoke<BOOL>(0xBFD6AE3D, p0); } // 0xBFD6AE3D
   static int GET_ACTOR_UPDATE_PRIORITY(Any p0) { return invoke<int>(0x6D322CD3, p0); } // 0x6D322CD3
   static void SET_ACTOR_UPDATE_PRIORITY(Any p0, Any p1) { invoke<Void>(0x44C05EF6, p0, p1); } // 0x44C05EF6
   static int _0xA4E29C31(Any p0, Any p1) { return invoke<int>(0xA4E29C31, p0, p1); } // 0xA4E29C31
   static int _0x5C7F63E3(Any p0) { return invoke<int>(0x5C7F63E3, p0); } // 0x5C7F63E3
   static int _ACTOR_IN_WORLD_ITERATOR(Any p0, float p1) { return invoke<int>(0x87C49DBD, p0, p1); } // 0x87C49DBD
   static Any _0xB42EBC65(Any result) { return invoke<Any>(0xB42EBC65, result); } // 0xB42EBC65
   static float* _0x135EA21D(float p0) { return invoke<float*>(0x135EA21D, p0); } // 0x135EA21D (Mass, Size, ModelOffset)
   static float* _0xA393AC4E(float p0) { return invoke<float*>(0xA393AC4E, p0); }  // 0xA393AC4E (Mass, Size, ModelOffset)
   static void SET_NPC_TO_ACTOR_DAMAGE_SCALE_FACTOR(Any p0, Any p1) { invoke<Void>(0x05CFE1E9, p0, p1); } // 0x05CFE1E9
   static int SET_ACTOR_LOW_DROP_DAMAGE(int p0, float p1) { return invoke<int>(0x083903D1, p0, p1); } // 0x083903D1 
   static int SET_ACTOR_MEDIUM_DROP_DAMAGE(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7, float p8) { return invoke<int>(0x1540A309, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x1540A309
   static int SET_ACTOR_HIGH_DROP_DAMAGE(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7, float p8) { return invoke<int>(0x7CC57FDA, p0, p1, p2, p3, p4, p5, p6, p7, p8); }  // 0x7CC57FDA
   static void SET_ACTOR_DEATH_DROP_DISTANCE(Any p0, Any p1) { invoke<Void>(0x9F6B04C8, p0, p1); } // 0x9F6B04C8
   static void SET_DAMAGE_SCALE_ENABLE(Any p0, Any p1) { invoke<Void>(0xDA0CDC91, p0, p1); } // 0xDA0CDC91
   static void SET_CRIPPLE_ENABLE(Any p0, Any p1) { invoke<Void>(0x3AD31762, p0, p1); } // 0x3AD31762
   static void SET_CRIPPLE_FLAG(Any p0, Any p1) { invoke<Void>(0x0A9A99DF, p0, p1); } // 0x0A9A99DF
   static BOOL IS_ACTOR_CRIPPLED(Any p0, Any p1) { return invoke<BOOL>(0x38C5F63F, p0, p1); } // 0x38C5F63F
   static int _0xA5A24484(Any p0) { return invoke<int>(0xA5A24484, p0); } // 0xA5A24484
   static void SET_ALLOW_COLD_WEATHER_BREATH(Any p0, Any p1) { invoke<Void>(0xA4677DD2, p0, p1); } // 0xA4677DD2
   static int _0x1F0CD262(Any p0) { return invoke<int>(0x1F0CD262, p0); } // 0x1F0CD262
   static void SET_EMOTION(Any p0, Any p1, Any p2) { invoke<Void>(0x1D1D9387, p0, p1, p2); } // 0x1D1D9387
   static int SET_ACTOR_STOP_UPDATE(Any p0, Any p1) { return invoke<int>(0xC0F77310, p0, p1); } // 0xC0F77310
   static int GET_ACTOR_STOP_UPDATE(Any p0) { return invoke<int>(0x4EFC58BC, p0); } // 0x4EFC58BC
   static BOOL IS_ACTOR_IN_ROOM(Any p0) { return invoke<BOOL>(0x22558E3F, p0); }  // 0x22558E3F
   static void REGISTER_TRAFFIC_OBJECTSET(Any p0) { invoke<Void>(0x398735FA, p0); } // 0x398735FA
   static void REGISTER_TRAFFIC_ACTOR(Any p0, Any p1) { invoke<Void>(0x398735FA, p0, p1); } // 0x67FA18A1
   static void REGISTER_GPS_CURVE_OBJECTSET(Any p0) { invoke<Void>(0x1444F022, p0); } // 0x1444F022
   static float* _0x4B90D22A(float p0) { return invoke<float*>(0x4B90D22A, p0); } // 0x4B90D22A (Mass, Size, ModelOffset)
   static float* _0xF1779E65() { return invoke<float*>(0xF1779E65); } // 0xF1779E65
   static int* _0xA819497B(float p0, float p1) { return invoke<int*>(0xA819497B, p0, p1); } // 0xA819497B
   static Any _0x8BE2D8B0(Any p0) { return invoke<Any>(0x8BE2D8B0, p0); } // 0x8BE2D8B0
   static int _0x91BB8548(Any p0, Any p1) { return invoke<int>(0x91BB8548, p0, p1); } // 0x91BB8548
   static BOOL _0x8AE58EE1(Any p0) { return invoke<BOOL>(0x8AE58EE1, p0); } // 0x8AE58EE1
   static void FEED_CODE_WARP_DIST(Any p0) { invoke<Void>(0xDE0E96F3, p0); } // 0xDE0E96F3
   static int _0x0911BA31(Any p0, Any p1) { return invoke<int>(0x0911BA31, p0, p1); } // 0x0911BA31
}

namespace POPULATION
{
   static int _0x1344515B() { return invoke<int>(0x1344515B); } // 0x1344515B
   static int _0x364F41D6() { return invoke<int>(0x364F41D6); } // 0x364F41D6
   static int LINK_ACTOR_ENUM_TO_POPULATION(Any p0, Any p1, float p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<int>(0x0C1B8DEA, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x0C1B8DEA
   static int LINK_ACTOR_ENUM_TO_POPULATION_TIMED(Any p0, Any p1, float p2, Any p3) { return invoke<int>(0x93B6135B, p0, p1, p2, p3); } // 0x93B6135B
   static int _UNLINK_ACTOR_ENUM_FROM_POPULATION(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<int>(0x84F75008, p0, p1, p2, p3, p4, p5, p6); } // 0x84F75008
   static void SET_ACCESSORYSET_ON_SPAWN(Any p0, Any p1, Any p2) { invoke<Void>(0xC79F2BD3, p0, p1, p2); } // 0xC79F2BD3
   static int _0x5996941F(Any p0, Any p1) { return invoke<int>(0x5996941F, p0, p1); } // 0x5996941F
   static void SET_ZONE_POPULATION_COUNT(Any p0, Any p1) { invoke<Void>(0x1B271D85, p0, p1); } // 0x1B271D85
   static void SET_ZONE_POPULATION_COUNT_RANDOM(Any p0, Any p1, Any p2) { invoke<Void>(0xE339719A, p0, p1, p2); } // 0xE339719A
   static void SET_ZONE_POPULATION_DENSITY(Any p0, Any p1) { invoke<Void>(0x9381D459, p0, p1); } // 0x9381D459
   static void SET_ZONE_POPULATION_TYPE(Any p0, Any p1) { invoke<Void>(0xFC30948B, p0, p1); } // 0xFC30948B
   static int SET_ZONE_POPULATION_SPAWN_MULTI_PER_POINT(Any p0, Any p1) { return invoke<int>(0x7D4FB8C8, p0, p1); } // 0x7D4FB8C8
   static int SET_ZONE_RESTRICT_ACTORS(Any p0, Any p1) { return invoke<int>(0xE0FDD026, p0, p1); } // 0xE0FDD026
   static int _0x0B24CE10(Any p0, Any p1) { return invoke<int>(0x0B24CE10, p0, p1); } // 0x0B24CE10
   static int _0x07FD0A76(Any p0, Any p1) { return invoke<int>(0x07FD0A76, p0, p1); } // 0x07FD0A76
   static int _0xE4A789D8(Any p0, Any p1) { return invoke<int>(0xE4A789D8, p0, p1); } // 0xE4A789D8
   static int _SET_ZONE_MAX_PER_CELL(Any p0, Any p1) { return invoke<int>(0x354DDFED, p0, p1); } // 0x354DDFED
   static int _0x7ABDE1F0() { return invoke<int>(0x7ABDE1F0); } // 0x7ABDE1F0
   static int _0x7D7F9770() { return invoke<int>(0x7D7F9770); } // 0x7D7F9770
   static void SET_ZONE_PRIORITY(Any p0, Any p1) { invoke<Void>(0x4B8C0945, p0, p1); } // 0x4B8C0945
   static int SET_ZONE_FORCE_SPAWN_DISTANCE(Any p0, float p1) { return invoke<int>(0xE7F19909, p0, p1); } // 0xE7F19909
   static int SET_ZONE_RESERVE_GRINGOS(Any p0, Any p1) { return invoke<int>(0xC43C4D76, p0, p1); } // 0xC43C4D76
   static int SET_ZONE_SPAWN_ONLY_AT_GRINGOS(Any p0, Any p1) { return invoke<int>(0xD72DF5C6, p0, p1); } // 0xD72DF5C6
   static int CLEAR_ZONE_ALLOWED_GRINGO_TYPE_LIST(Any p0) { return invoke<int>(0x230AB95E, p0); } // 0x230AB95E
   static void ADD_TO_ZONE_ALLOWED_GRINGO_TYPE_LIST(Any p0, Any p1) { invoke<Void>(0x64799CEE, p0, p1); } // 0x64799CEE
   static int SET_ZONE_RESPECT_VOLUME_RESTRICTIONS(Any p0, Any p1, Any p2) { return invoke<int>(0xFCA83D15, p0, p1, p2); } // 0xFCA83D15
   static int _0x04EFC113(float p0) { return invoke<int>(0x04EFC113, p0); } // 0x04EFC113
   static int _0xD28A3706(Any p0) { return invoke<int>(0xD28A3706, p0); } // 0xD28A3706
   static int _GET_RAND_ACTOR_ENUM_FROM_POPULATION_NATIVE(Any p0, Any p1, Any p2, Any p3, Any p4, float p5, float p6, float p7) { return invoke<int>(0xD3503922, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xD3503922
   static void MAKE_NEXT_RAND_ACTORENUMS_UNIQUE(Any p0) { invoke<Void>(0x1CE58D42, p0); } // 0x1CE58D42
   static Any IS_POPULATION_SET_READY(Any p0, Any p1, Any p2) { return invoke<Any>(0xFA5EA974, p0, p1, p2); } // 0xFA5EA974
   static BOOL IS_POPULATION_SET_REQUIRED_RESIDENT(Any p0) { return invoke<BOOL>(0x76E416FD, p0); } // 0x76E416FD
   static Any FIND_NAMED_POPULATION_SET(Any p0) { return invoke<Any>(0x4646C335, p0); } // 0x4646C335
   static int _GET_NUM_ACTOR_ENUMS_IN_POPULATION(Any p0) { return invoke<int>(0x8FD12F97, p0); } // 0x8FD12F97
   static Any GET_ACTORENUM_IN_POPULATION(Any p0, Any p1) { return invoke<Any>(0xABEC5676, p0, p1); } // 0xABEC5676
   static Any GET_ACTORENUM_IN_POPULATION_WEIGHT(Any p0, Any p1) { return invoke<Any>(0xEDD44891, p0, p1); } // 0xEDD44891
   static int _0x72F6EED0() { return invoke<int>(0x72F6EED0); } // 0x72F6EED0
   static int _SET_ZONE_FORCE_SPAWN_DISTANCE_2(Any p0, Any p1) { return invoke<int>(0x84FB15FA, p0, p1); } // 0x84FB15FA
   static void AMBIENT_SPAWN_PRESTREAM_SET(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x687545BF, p0, p1, p2, p3, p4, p5); } // 0x687545BF
   static int _0x2B75F13E() { return invoke<int>(0x2B75F13E); } // 0x2B75F13E
}

namespace PROBE
{
   static int _0x7080E24A(Any p0, float p1) { return invoke<int>(0x7080E24A, p0, p1); } // 0x7080E24A
   static void _0x1D7845B7(Any p0) { invoke<Void>(0x1D7845B7, p0); } // 0x1D7845B7 Unused
}

namespace PROP
{
   static int _0xDB70DF0C(int* p0, Any p1) { return invoke<int>(0xDB70DF0C, p0, p1); } // 0xDB70DF0C
   static int _0x6517FF1B(Any p0) { return invoke<int>(0x6517FF1B, p0); } // 0x6517FF1B
   static BOOL IS_PROP_FIXED(Any p0) { return invoke<BOOL>(0xBD2FFD8C, p0); } // 0xBD2FFD8C
   static void SET_PROP_FIXED(Any p0, Any p1) { invoke<Void>(0x7DBB277A, p0, p1); } // 0x7DBB277A
   static int REMOVE_PHYSINST(Any p0) { return invoke<int>(0x2E5A224C, p0); } // 0x2E5A224C
   static int _0x31940E4C(Any p0, Any p1) { return invoke<int>(0x31940E4C, p0, p1); } // 0x31940E4C
   static int HAS_PROP_BEEN_DAMAGED(Any p0) { return invoke<int>(0x7151E7F0, p0); } // 0x7151E7F0
   static float GET_PROP_HEALTH(Any p0) { return invoke<float>(0xFDC6E853, p0); } // 0xFDC6E853
   static void SET_PROP_HEALTH(Any p0, Any p1) { invoke<Void>(0xC6D12FF5, p0, p1); } // 0xC6D12FF5
   static int* RESET_PROPS_IN_WORLD() { return invoke<int*>(0xB3E331AC); } // 0xB3E331AC
   static void RESET_PROPS_IN_VOLUME(Any p0, Any p1) { invoke<Void>(0xCF1B9B11, p0, p1); } // 0xCF1B9B11
   static void RESET_PROP(Any p0) { invoke<Void>(0x5E7A7E9B, p0); } // 0x5E7A7E9B
   static void SET_PROP_TARGETABLE(Any p0, Any p1, Any p2) { invoke<Void>(0x32C810BF, p0, p1, p2); } // 0x32C810BF
   static void SET_PROP_TARGETABLE_ACQUISITION_RADIUS(Any p0, Any p1) { invoke<Void>(0xE84EB2D5, p0, p1); } // 0xE84EB2D5
   static void SET_PROP_TARGETABLE_TARGET_BOX_SIZE(Any p0, Any p1, Any p2) { invoke<Void>(0x6A937CBB, p0, p1, p2); } // 0x6A937CBB
   static void SET_PROP_TARGETABLE_SCORE_BIAS(Any p0, Any p1) { invoke<Void>(0x0E2B0212, p0, p1); }  // 0x0E2B0212
   static void SET_PROP_TARGETABLE_AS_ENEMY(Any p0, Any p1) { invoke<Void>(0x5895EBBE, p0, p1); } // 0x5895EBBE
   static int SET_PROP_CAUSE_ARM_UP(Any p0, Any p1) { return invoke<int>(0xCC004171, p0, p1); } // 0xCC004171
   static BOOL IS_PROP_STREAMED_IN(Any p0) { return invoke<BOOL>(0x5131AEF1, p0); } // 0x5131AEF1
   static BOOL GRAVE_IS_DUG_UP(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<BOOL>(0x935F80FF, p0, p1, p2, p3, p4, p5); } // 0x935F80FF
   static void GRAVE_SET_DUG_UP(Any p0, Any p1) { invoke<Void>(0x674156BB, p0, p1); } // 0x674156BB
   static int GET_GRAVE_FROM_OBJECT(Any p0) { return invoke<int>(0xA90E602F, p0); } // 0xA90E602F
   static int PLAY_SIMPLE_PROP_ANIMATION(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0xDC3FBAE6, p0, p1, p2, p3, p4, p5); } // 0xDC3FBAE6
   static void SET_DRAW_OBJECT(Any p0, Any p1) { invoke<Void>(0xC5A886DC, p0, p1); } // 0xC5A886DC
   static int _0xCED86AF7(Any p0) { return invoke<int>(0xCED86AF7, p0); } // 0xCED86AF7
   static int _FRAGMENT_IS_VARIABLE_MESH_ENABLED(Any p0, Any p1) { return invoke<int>(0x375A33F0, p0, p1); } // 0x375A33F0
   static int __FRAGMENT_IS_VARIABLE_MESH_ENABLED_2(Any p0, Any p1, Any p2) { return invoke<int>(0x8287F8B3, p0, p1, p2); } // 0x8287F8B3
   static int _0x4BCFADB1(Any p0, Any p1) { return invoke<int>(0x4BCFADB1, p0, p1); } // 0x4BCFADB1
   static int _0x6D555332(Any p0) { return invoke<int>(0x6D555332, p0); } // 0x6D555332
}

namespace RENDER
{
   static Any _0x6AF07F86(Any p0) { return invoke<Any>(0x6AF07F86, p0); }  // 0x6AF07F86
   static void PRINT_FRAME_TIME(Any p0) { invoke<Void>(0xB84DE79E, p0); } // 0xB84DE79E
}

namespace RETICLE
{
   static int _ACTOR_RETICLE(int* p0, Any p1, Any p2) { return invoke<int>(0x86BAAC6C, p0, p1, p2); } // 0x86BAAC6C
   static int _0x8AE7281E(Any p0, Any p1) { return invoke<int>(0x8AE7281E, p0, p1); } // 0x8AE7281E
   static int _0x5F566576(Any p0, Any p1) { return invoke<int>(0x5F566576, p0, p1); } // 0x5F566576
   static int _0xD95C01D2(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, float p8, float p9) { return invoke<int>(0xD95C01D2, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xD95C01D2
   static int SET_ACTOR_BASE_SCORE(Any p0, float p1, Any p2, Any p3) { return invoke<int>(0x91220723, p0, p1, p2, p3); } // 0x91220723
   static int _0x856C3A8A(Any p0, float p1, Any p2, Any p3) { return invoke<int>(0x856C3A8A, p0, p1, p2, p3); } // 0x856C3A8A
   static int _0x6400E005(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<int>(0x6400E005, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x6400E005
   static int _0xF1607937(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<int>(0xF1607937, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xF1607937
   static int _0x0753A098(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<int>(0x0753A098, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x0753A098
   static int _0xF4429710(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<int>(0xF4429710, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xF4429710
   static BOOL _0x1468DD56(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<BOOL>(0x1468DD56, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x1468DD56
   static int _0x327E4426(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<int>(0x327E4426, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x327E4426
   static void _0xAC8D3A0C(Any p0, Any p1) { invoke<Void>(0xAC8D3A0C, p0, p1); } // 0xAC8D3A0C
   static void _0x57055A7D(Any p0, Any p1) { invoke<Void>(0x57055A7D, p0, p1); } // 0x57055A7D
   static void _0x5CC16A49(Any p0, Any p1) { invoke<Void>(0x5CC16A49, p0, p1); } // 0x5CC16A49
   static void _0x7E124E62() { invoke<Void>(0x7E124E62); } // 0x7E124E62
   static void _0x1EEE7494(Any p0, Any p1) { invoke<Void>(0x1EEE7494, p0, p1); } // 0x1EEE7494
   static float _0xD19EFFC1(Any p0, Any p1) { return invoke<float>(0xD19EFFC1, p0, p1); } // 0xD19EFFC1
}

namespace SHOP
{
   static int SHOP_CLEAR(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xCEBD595A, p0, p1, p2, p3); } // 0xCEBD595A
   static void SHOP_REFRESH(Any p0) { invoke<Void>(0xE7F6AA5D, p0); } // 0xE7F6AA5D
   static void SHOP_SET_PLAYER_BANK(Any p0) { invoke<Void>(0xB75FAD6A, p0); }// 0xB75FAD6A
   static int SHOP_ADD_ITEM(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0x2FCD8CCA, p0, p1, p2, p3, p4, p5); } // 0x2FCD8CCA
   static int SHOP_SET_ITEM_QUANTITY(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x777CF9FA, p0, p1, p2, p3); } // 0x777CF9FA
   static int SHOP_GET_ITEM_QUANTITY(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0xFAF37414, p0, p1, p2, p3, p4); } // 0xFAF37414
   static int SHOP_SET_ITEM_PURCHASE_PRICE(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xA40EFFFF, p0, p1, p2, p3); } // 0xA40EFFFF
   static int SHOP_GET_ITEM_PURCHASE_PRICE(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x94D8F49E, p0, p1, p2, p3, p4); } // 0x94D8F49E
   static int SHOP_GET_ITEM_SELL_PRICE(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x42CBA241, p0, p1, p2, p3, p4); } // 0x42CBA241
   static int SHOP_SET_ITEM_BLOCKED(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x7A34C33D, p0, p1, p2, p3); } // 0x7A34C33D
   static int SHOP_IS_ITEM_BLOCKED(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xB954DE78, p0, p1, p2, p3); } // 0xB954DE78
   static int SHOP_GET_ITEM_MISC_FLAG(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x1BF8FD6D, p0, p1, p2, p3); } // 0x1BF8FD6D
   static BOOL SHOP_IS_SELL_SELECTED(Any p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0x5A12BB48, p0, p1, p2, p3); } // 0x5A12BB48
   static int SHOP_SET_CURRENT_TAB(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x3601E3E2, p0, p1, p2, p3); } // 0x3601E3E2
   static int SHOP_LOCK_INPUT(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0xB84DE662, p0, p1, p2, p3, p4); } // 0xB84DE662
   static int SATCHEL_SET_ENABLED() { return invoke<int>(0x2692B771); } // 0x2692B771
   static int SATCHEL_TOGGLE_NO_PAUSE_OUTFIT(const char* p0) { return invoke<int>(0xEB046CD9, p0); } // 0xEB046CD9
   static int SATCHEL_CREATE_OUTFIT(Any p0, Any p1, Any p2) { return invoke<int>(0x427F4D58, p0, p1, p2); } // 0x427F4D58
   static int SATCHEL_SET_OUTFIT_STATE(Any p0, Any p1) { return invoke<int>(0x0A87A573, p0, p1); } // 0x0A87A573
   static int SATCHEL_GET_OUTFIT_STATE(Any p0) { return invoke<int>(0x25EF49AD, p0); } // 0x25EF49AD
   static int SATCHEL_SET_OUTFIT_TEXTURE(Any p0, Any p1) { return invoke<int>(0x23EB81F0, p0, p1); } // 0x23EB81F0
   static int SATCHEL_ALLOW_OUTFIT_CHANGE(const char* p0) { return invoke<int>(0x58018D83, p0); } // 0x58018D83
   static int SATCHEL_SET_CURRENT_OUTFIT(Any p0) { return invoke<int>(0x1C462085, p0); } // 0x1C462085
}

namespace SIMULATOR
{
   static int GET_PHYSINST_VELOCITY(Any p0, Any p1) { return invoke<int>(0x17B69196, p0, p1); } // 0x17B69196
   static BOOL IS_PHYSINST_ACTIVE(Any p0) { return invoke<BOOL>(0xAFB1DFA2, p0); } // 0xAFB1DFA2
   static void _0x38636EBF(Any p0, Any p1) { invoke<Void>(0x38636EBF, p0, p1); } // 0x38636EBF
   static void SET_PHYSINST_FROZEN(Any p0, Any p1) { invoke<Void>(0x2C0AF634, p0, p1); } // 0x2C0AF634
   static BOOL IS_PHYSINST_FROZEN(Any p0) { return invoke<BOOL>(0x789AA2B2, p0); } // 0x789AA2B2
   static int SET_PHYSINST_HIDE(Any p0) { return invoke<int>(0xEBD9DFE6, p0); } // 0xEBD9DFE6
   static BOOL IS_PHYSINST_HIDE(Any p0) { return invoke<BOOL>(0x445990D8, p0); } // 0x445990D8
   static void BREAK_OFF_ABOVE(Any p0, Any p1) { invoke<Void>(0xB5F9F4CF, p0, p1); }// 0xB5F9F4CF
   static int GET_LOCATOR_OFFSETS(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x0BA5E579, p0, p1, p2, p3); } // 0x0BA5E579
   static int _0xFD759593(Any p0, Any p1) { return invoke<int>(0xFD759593, p0, p1); } // 0xFD759593
   static int _0x87A2C1D5(const char* p0) { return invoke<int>(0x87A2C1D5, p0); } // 0x87A2C1D5
   static int _0x374DE883(Any p0) { return invoke<int>(0x374DE883, p0); } // 0x374DE883
   static int _0x89B45C7D(float p0) { return invoke<int>(0x89B45C7D, p0); } // 0x89B45C7D
   static int _0x4C02E1E5() { return invoke<int>(0x4C02E1E5); } // 0x4C02E1E5
}

namespace SOCIALCLUB
{
   static Any DISABLE_PLAYER_GRINGO_USE(Any p0, Any p1) { return invoke<Any>(0x6FCF6BC8, p0, p1); } // 0x6FCF6BC8
   static Any _0x5A9D0738(Any p0) { return invoke<Any>(0x5A9D0738, p0); } // 0x5A9D0738
   static void _0x15040CD2(Any p0) { invoke<Void>(0x15040CD2, p0); } // 0x15040CD2
   static void _0x45589499(Any p0) { invoke<Void>(0x45589499, p0); } // 0x45589499
   static int GET_GAME_STATE() { return invoke<int>(0xDD9BD22B); } // 0xDD9BD22B
   static void SET_PAUSE_SCRIPT(Any p0) { invoke<Void>(0x9B71351C, p0); } // 0x9B71351C
   static Any ENABLE_USE_CONTEXTS(Any p0) { return invoke<Any>(0xFEA58D57, p0); } // 0xFEA58D57
   static Any _0x2ADA3DD4() { return invoke<Any>(0x2ADA3DD4); } // 0x2ADA3DD4
   static Any IS_SCRIPT_USE_CONTEXT_VALID(Any p0) { return invoke<Any>(0x115CD0CC, p0); } // 0x115CD0CC
   static Any ADD_SCRIPT_USE_CONTEXT_IN_VOLUME(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13, Any p14, Any p15) { return invoke<Any>(0x039E7F1D, p0, p1, p2, p3, p4, p5, p6, p7, p8, p8, p10, p11, p12, p13, p14, p14, p15); } // 0x039E7F1D
   static int ADD_SCRIPT_USE_CONTEXT(const char* gxtName, Any p1, int button, Any p3, Any p4, Any p5, Any p6, int p7, Any p8) { return invoke<int>(0xD7591B0E, gxtName, p1, button, p3, p4, p5, p6, p7, p8); } // 0xD7591B0E
   static Any _0xF48F8F09(Any p0) { return invoke<Any>(0xF48F8F09, p0); } // 0xF48F8F09
   static Any IS_SCRIPT_USE_CONTEXT_PRESSED(Any p0) { return invoke<Any>(0x45C1C061, p0); } // 0x45C1C061
   static Any WAS_SCRIPT_USE_CONTEXT_EVER_PRESSED(Any p0) { return invoke<Any>(0x971559CA, p0); } // 0x971559CA
   static Any _SETTING_USE_CONTEXT_STRING(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<Any>(0x3ECD8FEE, p0, p1, p2, p3, p4, p5, p6); } // 0x3ECD8FEE
   static Any RELEASE_SCRIPT_USE_CONTEXT(Any p0) { return invoke<Any>(0x4F52CB58, p0); } // 0x4F52CB58
   static Any NET_MAILBOX_IS_SIGNED_INTO_SC() { return invoke<Any>(0xA3E1EF71); } // 0xA3E1EF71
   static Any NET_MAILBOX_GET_MAX_NUM_CHALLENGES() { return invoke<Any>(0x6B439149); } // 0x6B439149
   static Any NET_MAILBOX_GET_NUM_CHALLENGES() { return invoke<Any>(0x89F1B8CD); } // 0x89F1B8CD
   static Any NET_MAILBOX_GET_CHALLENGE_BY_INDEX(Any p0) { return invoke<Any>(0xE85942F0, p0); } // 0xE85942F0
   static Any NET_MAILBOX_GET_CHALLENGE_BY_ID(Any p0) { return invoke<Any>(0xD4FBCCE0, p0); } // 0xD4FBCCE0
   static Any NET_MAILBOX_IS_CHALLENGE_VALID(Any p0) { return invoke<Any>(0xC9E96F78, p0); } // 0xC9E96F78
   static Any SC_CHALLENGE_LAUNCH(Any p0) { return invoke<Any>(0xCBBE41DD, p0); } // 0xCBBE41DD
   static Any SC_CHALLENGE_CLEAN_UP(Any p0) { return invoke<Any>(0xB7DE2AF2, p0); } // 0xB7DE2AF2
   static Any SC_CHALLENGE_IS_RUNNING(Any p0) { return invoke<Any>(0x79F09AC7, p0); } // 0x79F09AC7
   static Any SC_CHALLENGE_IS_ACTIVE(Any p0, Any p1) { return invoke<Any>(0x5D7197BC, p0, p1); } // 0x5D7197BC
   static Any SC_CHALLENGE_GET_COMMUNITY_TOTAL(Any p0) { return invoke<Any>(0xFFC55DA4, p0); } // 0xFFC55DA4
   static Any SC_CHALLENGE_GET_COMMUNITY_VALUE(Any p0) { return invoke<Any>(0xCEEEAE1D, p0); } // 0xCEEEAE1D
   static Any SC_CHALLENGE_PROCESS_EXPIRATION(Any p0) { return invoke<Any>(0x1876B04E, p0); } // 0x1876B04E
   static Any SC_CHALLENGE_GET_EXPIRATION_STATE(Any p0) { return invoke<Any>(0x4BD61354, p0); } // 0x4BD61354
   static Any SC_CHALLENGE_RESET_EXPIRATION_STATE(Any p0) { return invoke<Any>(0xF5F97702, p0); } // 0xF5F97702
   static Any _0xFD6197EB(Any p0, Any p1) { return invoke<Any>(0xFD6197EB, p0, p1); } // 0xFD6197EB
   static Any SC_CHALLENGE_GET_VAR_FLOAT(Any p0, Any p1, Any p2) { return invoke<Any>(0xC322556E, p0, p1, p2); } // 0xC322556E
   static Any SC_CHALLENGE_GET_VAR_INT(Any p0, Any p1) { return invoke<Any>(0x2390DD18, p0, p1); } // 0x2390DD18
   static Any SC_CHALLENGE_GET_VAR_BOOL(Any p0, Any p1) { return invoke<Any>(0xB40622F1, p0, p1); } // 0xB40622F1
   static Any SC_CHALLENGE_RELEASE(Any p0) { return invoke<Any>(0xD2513200, p0); } // 0xD2513200
   static Any SC_CHALLENGE_GET_LEADERBOARD_ID(Any p0, Any p1, Any p2) { return invoke<Any>(0xC21048BF, p0, p1, p2); } // 0xC21048BF
   static Any _0x5725C84F(Any p0) { return invoke<Any>(0x5725C84F, p0); } // 0x5725C84F
   static Any _0x2374C1E0(Any p0) { return invoke<Any>(0x2374C1E0, p0); } // 0x2374C1E0
}

namespace SQUAD
{
   static int SQUAD_GET(Any p0) { return invoke<int>(0xB3732081, p0); } // 0xB3732081
   static Any SQUAD_IS_VALID(Any p0) { return invoke<Any>(0xBDB3061E, p0); } // 0xBDB3061E
   static void SQUAD_JOIN(Any p0, Any p1) { invoke<Void>(0xB14302C8, p0, p1); } // 0xB14302C8
   static void SQUAD_LEAVE(Any p0) { invoke<Void>(0x077591FF, p0); } // 0x077591FF
   static void SQUAD_MAKE_EMPTY(Any p0) { invoke<Void>(0x90D92CF1, p0); } // 0x90D92CF1
   static void SQUADS_MERGE(Any p0, Any p1) { invoke<Void>(0x320E2604, p0, p1); } // 0x320E2604
   static Any SQUAD_GET_ACTOR_BY_INDEX(Any p0, Any p1) { return invoke<Any>(0x5126039A, p0, p1); } // 0x5126039A
   static Any SQUAD_GET_SIZE(Any p0) { return invoke<Any>(0xEEC83187, p0); } // 0xEEC83187
   static int _0x142D9F3A(Any p0, Any p1) { return invoke<int>(0x142D9F3A, p0, p1); } // 0x142D9F3A
   static void SQUAD_SET_FACTION(Any p0, Any p1) { invoke<Void>(0xAEA4E9AE, p0, p1); } // 0xAEA4E9AE
   static int SQUAD_GOAL_ADD_BATTLE_ALLIES(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x65888454, p0, p1, p2, p3); } // 0x65888454
   static int SQUAD_GOAL_ADD_BATTLE_DEFEND_VOLUME(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xD52A28F0, p0, p1, p2, p3); } // 0xD52A28F0
   static int _0x4DD06256(int* p0, Any p1, Any p2, Any p3) { return invoke<int>(0x4DD06256, p0, p1, p2, p3); } // 0x4DD06256
   static int _0xA4BC2A1B(int* p0, Any p1, Any p2) { return invoke<int>(0xA4BC2A1B, p0, p1, p2); } // 0xA4BC2A1B
   static int SQUAD_GOAL_ADD_FLOCK(Any p0, Any p1, Any p2) { return invoke<int>(0x9D3B103C, p0, p1, p2); } // 0x9D3B103C
   static int SQUAD_GOAL_ADD_FOLLOW_OBJECT_IN_FORMATION(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0x1AC03C80, p0, p1, p2, p3, p4, p5); } // 0x1AC03C80
   static int SQUAD_GOAL_ADD_FOLLOW_PATH_IN_FORMATION(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return invoke<int>(0x750C1A2B, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x750C1A2B
   static int SQUAD_GOAL_ADD_FOLLOW_TRAFFIC_CURVE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<int>(0xE77B9FC0, p0, p1, p2, p3, p4, p5, p6); } // 0xE77B9FC0
   static int SQUAD_GOAL_ADD_GENERAL_TASK(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x83D78A49, p0, p1, p2, p3); } // 0x83D78A49
   static int _0x8BA55E8D(int* p0, Any p1, Any p2, float p3) { return invoke<int>(0x8BA55E8D, p0, p1, p2, p3); } // 0x8BA55E8D
   static int _0x96DB0BA1(int* p0, Any p1, float p2, float p3, float p4) { return invoke<int>(0x96DB0BA1, p0, p1, p2, p3, p4); } // 0x96DB0BA1
   static int SQUAD_GOAL_ADD_MEET_AT_POSITION(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0xA2AE53BD, p0, p1, p2, p3, p4, p5); } // 0xA2AE53BD
   static int _0x35051831(int* p0, Any p1, float p2) { return invoke<int>(0x35051831, p0, p1, p2); } // 0x35051831
   static int _0x435A982F(int* p0, Any p1) { return invoke<int>(0x435A982F, p0, p1); } // 0x435A982F
   static int SQUAD_GOAL_ADD_STAY_OUTSIDE_OF_VOLUME(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x5F4DEC49, p0, p1, p2, p3, p4); } // 0x5F4DEC49
   static int SQUAD_GOAL_ADD_STAY_WITHIN_VOLUME(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0xE775EF0D, p0, p1, p2, p3, p4); } // 0xE775EF0D
   static int _0x48588CCB(int* p0, Any p1, Any p2, Any p3) { return invoke<int>(0x48588CCB, p0, p1, p2, p3); } // 0x48588CCB
   static int _0xC6AF3662(int* p0, Any p1) { return invoke<int>(0xC6AF3662, p0, p1); } // 0xC6AF3662
   static BOOL _0xFAD7A113(Any p0) { return invoke<int>(0xFAD7A113, p0); } // 0xFAD7A113
   static int SQUAD_GOAL_REMOVE(Any p0, Any p1) { return invoke<int>(0xBB3A34B0, p0, p1); } // 0xBB3A34B0
   static Any _0xCA950EF0(Any p0) { return invoke<Any>(0xCA950EF0, p0); } // 0xCA950EF0
   static int SQUAD_IS_GOAL_CONTROLLING_ACTOR(Any p0, Any p1, Any p2) { return invoke<int>(0x817AC6D6, p0, p1, p2); } // 0x817AC6D6
   static int SQUAD_GET_SINGLE_ACTOR_CONTROLLED_BY_GOAL(Any* p0, Any p1, Any p2) { return invoke<int>(0xF37E8A9E, p0, p1, p2); } // 0xF37E8A9E
   static int SQUAD_GOAL_LINK_MODIFIER_TO_OTHER_GOAL(Any p0, Any p1, Any p2) { return invoke<int>(0x1B74CCA1, p0, p1, p2); } // 0x1B74CCA1
   static void SQUAD_FLOCK_SET_EXTERNAL_MOVEMENT_TUNING(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x224CFE5B, p0, p1, p2, p3, p4); } // 0x224CFE5B
   static int SQUAD_FLOCK_SET_FLOCKING_PARAMETER(Any p0, Any p1, Any p2, Any p3, Any p4, float p5) { return invoke<int>(0x3F9736B8, p0, p1, p2, p3, p4, p5); } // 0x3F9736B8
   static int SQUAD_FLOCK_SET_BOOL_FLOCKING_PARAMETER(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0x5E24EAA0, p0, p1, p2, p3, p4, p5); } // 0x5E24EAA0
   static void SQUAD_FLOCK_ADD_EXTERNAL_ALERT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x1F0E5B88, p0, p1, p2, p3, p4, p5); } // 0x1F0E5B88
   static void SQUAD_FLOCK_ADD_EXTERNAL_ATTRACTION_PATH(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x895AA97B, p0, p1, p2, p3, p4, p5, p6); } // 0x895AA97B
   static void SQUAD_FLOCK_ADD_EXTERNAL_REPULSION(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x53609885, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x53609885
   static void SQUAD_FLOCK_ADD_EXTERNAL_VELOCITY_MATCH(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xE8B7AA08, p0, p1, p2, p3, p4, p5); } // 0xE8B7AA08
   static void SQUAD_FLOCK_PLAYER_PROXIMITY_BOOST_SET_ENABLED(Any p0, Any p1, Any p2) { invoke<Void>(0xE4E94286, p0, p1, p2); } // 0xE4E94286
   static void SQUAD_FLOCK_PLAYER_WHISTLE_BOOST_SET_ENABLED(Any p0, Any p1, Any p2) { invoke<Void>(0x6770774F, p0, p1, p2); } // 0x6770774F
   static int SQUAD_FLOCK_EVENT_BOOST_SET_ENABLED(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x5A43D915, p0, p1, p2, p3); } // 0x5A43D915
   static int _SQUAD_FLOCK_GET_FLOCKING_PARAMETER_2(Any p0, Any p1, Any p2, Any p3, float p4) { return invoke<int>(0x175BE678, p0, p1, p2, p3, p4); } // 0x175BE678
   static int _SQUAD_FLOCK_CLEAR_EXTERNAL_INFLUENCES(Any p0, Any p1) { return invoke<int>(0x5AEA32D1, p0, p1); } // 0x5AEA32D1
   static int _SQUAD_FLOCK_CLEAR_EXTERNAL_INFLUENCES_FROM_OBJECT(Any p0, Any p1, Any p2) { return invoke<int>(0x484643F6, p0, p1, p2); } // 0x484643F6
   static int _SQUAD_FLOCK_ADD_EXTERNAL_ALERT_2(Any p0, Any p1, Any p2, float p3, float p4) { return invoke<int>(0x1CEB8BFF, p0, p1, p2, p3, p4); } // 0x1CEB8BFF
   static int _SQUAD_FLOCK_ADD_EXTERNAL_REPULSION_2(Any p0, Any p1, Any p2, float p3, float p4, float p5, float p6, float p7) { return invoke<int>(0xB4D9B233, p0, p1, p2, p3, p4, p5, p6, p7); } // 0xB4D9B233
   static int SQUAD_FLOCK_SET_ALLOW_STRAGGLERS(Any p0, Any p1, Any p2) { return invoke<int>(0xFC24BB6A, p0, p1, p2); } // 0xFC24BB6A
   static int _0xE7A0A109(Any p0) { return invoke<int>(0xE7A0A109, p0); } // 0xE7A0A109
   static int _0x0073024E(Any p0) { return invoke<int>(0x0073024E, p0); } // 0x0073024E
   static int _0x82C54B8A(Any p0, float p1) { return invoke<int>(0x82C54B8A, p0, p1); } // 0x82C54B8A
   static int _0x57C67E91(Any p0) { return invoke<int>(0x57C67E91, p0); } // 0x57C67E91
   static int _0x55DAC120(Any p0) { return invoke<int>(0x55DAC120, p0); } // 0x55DAC120
   static void SQUAD_SET_NOT_ELIMINATED_IMPAIRMENT_MASK(Any p0, Any p1) { invoke<Void>(0xE7D45FB3, p0, p1); } // 0xE7D45FB3
   static int _0xAEDD7512(Any p0) { return invoke<int>(0xAEDD7512, p0); } // 0xAEDD7512
   static int SQUAD_BATTLE_ALLIES_SET_OBJECTIVE(Any p0, Any p1, Any p2) { return invoke<int>(0x907D4081, p0, p1, p2); }  // 0x907D4081
   static void SQUAD_BATTLE_ALLIES_SET_FORMATION_DENSITY(Any p0, Any p1, Any p2) { invoke<Void>(0x6BC42101, p0, p1, p2); } // 0x6BC42101
   static int SQUAD_FOLLOW_TRAFFIC_CURVE_GET_ALL_BEHAVIOR_FLAGS(Any p0, Any p1) { return invoke<int>(0xE21D4785, p0, p1); } // 0xE21D4785
   static int SQUAD_FOLLOW_TRAFFIC_CURVE_SET_ALL_BEHAVIOR_FLAGS(Any p0, Any p1, Any p2) { return invoke<int>(0xF3C07A17, p0, p1, p2); } // 0xF3C07A17
   static BOOL SQUAD_FOLLOW_TRAFFIC_CURVE_GET_BEHAVIOR_FLAG(Any p0, Any p1, Any p2) { return invoke<BOOL>(0x20009EB2, p0, p1, p2); } // 0x20009EB2
   static void SQUAD_FOLLOW_TRAFFIC_CURVE_SET_BEHAVIOR_FLAG(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x7FEE2B3C, p0, p1, p2, p3); } // 0x7FEE2B3C
   static int SQUAD_FOLLOW_TRAFFIC_CURVE_SET_CURVE(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x0031613E, p0, p1, p2, p3); } // 0x0031613E
   static void SQUAD_FOLLOW_TRAFFIC_CURVE_ENQUEUE_CURVE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x041C0802, p0, p1, p2, p3); } // 0x041C0802
   static int SQUAD_FOLLOW_TRAFFIC_CURVE_SET_SPEED(Any p0, Any p1) { return invoke<int>(0x347616C9, p0, p1); } // 0x347616C9
   static int SQUAD_FOLLOW_TRAFFIC_CURVE_SET_SPEED_ABSOLUTE(Any p0, Any p1, float p2) { return invoke<int>(0xB00F188D, p0, p1, p2); } // 0xB00F188D
   static int SQUAD_FOLLOW_TRAFFIC_CURVE_SET_SPEED_NORMALIZED(Any p0, Any p1, float p2) { return invoke<int>(0x70E0654A, p0, p1, p2); } // 0x70E0654A
   static void SQUAD_FOLLOW_TRAFFIC_CURVE_SET_TASK_PRIORITY(Any p0, Any p1, Any p2) { invoke<Void>(0x8C8EEEF2, p0, p1, p2); } // 0x8C8EEEF2
   static int SQUAD_FOLLOW_TRAFFIC_CURVE_SET_OFFSET_X(Any p0, Any p1, float p2) { return invoke<int>(0x0F163466, p0, p1, p2); } // 0x0F163466
   static int SQUAD_FOLLOW_TRAFFIC_CURVE_SET_DESIRED_LEADER(Any p0, Any p1, Any p2) { return invoke<int>(0x430993FC, p0, p1, p2); } // 0x430993FC
   static int _SQUAD_FOLLOW_TRAFFIC_CURVE_ALLOW_PLAYER_JOIN(Any p0) { return invoke<int>(0x430993FC, p0); } // 0x430993FC
   static int _0x27F7C1E4(int* p0, Any p1, Any p2) { return invoke<int>(0x27F7C1E4, p0, p1, p2); } // 0x27F7C1E4
   static int SQUAD_FOLLOW_TRAFFIC_CURVE_CLEAR_DESIRED_LEADER(Any p0, Any p1) { return invoke<int>(0x5BADEFDC, p0, p1); } // 0x5BADEFDC
   static int SQUAD_FOLLOW_TRAFFIC_CURVE_IS_CURVE_ALREADY_IN_LIST(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x8DC095B0, p0, p1, p2, p3, p4); } // 0x8DC095B0
   static int SQUAD_FOLLOW_PATH_IN_FORMATION_GET_ALL_BEHAVIOR_FLAGS(Any p0, Any p1) { return invoke<int>(0xE69AE6C5, p0, p1); } // 0xE69AE6C5
   static int SQUAD_FOLLOW_PATH_IN_FORMATION_SET_ALL_BEHAVIOR_FLAGS(Any p0, Any p1, Any p2) { return invoke<int>(0xFA63B0F7, p0, p1, p2); } // 0xFA63B0F7
   static BOOL SQUAD_FOLLOW_PATH_IN_FORMATION_GET_BEHAVIOR_FLAG(Any p0, Any p1, Any p2) { return invoke<BOOL>(0xC4D79095, p0, p1, p2); } // 0xC4D79095
   static int SQUAD_FOLLOW_PATH_IN_FORMATION_SET_BEHAVIOR_FLAG(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x5C14EC4E, p0, p1, p2, p3); } // 0x5C14EC4E
   static int SQUAD_FOLLOW_PATH_IN_FORMATION_SET_PATH(Any p0, Any p1, Any p2) { return invoke<int>(0x6FB2CADA, p0, p1, p2); } // 0x6FB2CADA
   static int SQUAD_FOLLOW_PATH_IN_FORMATION_SET_SPEED(Any p0) { return invoke<int>(0x437E2995, p0); } // 0x437E2995
   static int SQUAD_FOLLOW_PATH_IN_FORMATION_SET_SPEED_ABSOLUTE(Any p0, float p1) { return invoke<int>(0x7B681402, p0, p1); } // 0x7B681402
   static int SQUAD_FOLLOW_PATH_IN_FORMATION_SET_SPEED_NORMALIZED(Any p0, float p1) { return invoke<int>(0xD618C1C7, p0, p1); } // 0xD618C1C7
   static int SQUAD_FOLLOW_PATH_IN_FORMATION_SET_TASK_PRIORITY(Any p0, Any p1, Any p2) { return invoke<int>(0xF661D354, p0, p1, p2); } // 0xF661D354
   static int SQUAD_FOLLOW_PATH_IN_FORMATION_SET_OFFSET_X(Any p0, Any p1, float p2) { return invoke<int>(0x554EFABE, p0, p1, p2); } // 0x554EFABE
   static int _SQUAD_FOLLOW_PATH_IN_FORMATION_ALLOW_PLAYER_JOIN(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x3966E20B, p0, p1, p2); } // 0x3966E20B
   static int SQUAD_FOLLOW_PATH_IN_FORMATION_SET_NONSTOP(Any p0, Any p1, Any p2) { return invoke<int>(0x8BE72016, p0, p1, p2); } // 0x8BE72016
   static int SQUAD_FOLLOW_PATH_IN_FORMATION_SET_DESIRED_LEADER(Any p0, Any p1, Any p2) { return invoke<int>(0xA8A50DF5, p0, p1, p2); } // 0xA8A50DF5
   static int SQUAD_FOLLOW_PATH_IN_FORMATION_CLEAR_DESIRED_LEADER(Any p0, Any p1) { return invoke<int>(0x47F31A41, p0, p1); } // 0x47F31A41
}

namespace STAT
{
   static void CREATE_STAT(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x32A3A7AE, p0, p1, p2, p3); } // 0x32A3A7AE
   static void HIDE_STAT(Any p0, Any p1) { invoke<Void>(0x1CF1FCC4, p0, p1); } // 0x1CF1FCC4
   static void UPDATE_STAT(Any p0, Any p1, Any p2) { invoke<Void>(0xC9212F76, p0, p1, p2); } // 0xC9212F76
   static void ENABLE_JOURNAL_REPLAY(Any p0) { invoke<Void>(0x957F1618, p0); } // 0x957F1618
   static int SET_JOURNAL_INFO_LABEL(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0x40C2576F, p0, p1, p2, p3, p4); } // 0x40C2576F
   static float _0x5545C218(Any p0) { return invoke<float>(0x5545C218, p0); } // 0x5545C218
   static float _0xE623B382(Any p0) { return invoke<float>(0xE623B382, p0); } // 0xE623B382
   static void PUSH_COMMAND_HANDLE(Any p0, Any p1) { invoke<Void>(0x2104B1C0, p0, p1); } // 0x2104B1C0
   static int _0xF1A723D0(int result, float p1) { return invoke<int>(0xF1A723D0, result, p1); } // 0xF1A723D0
   static int _0xBBF4F7E4() { return invoke<int>(0xBBF4F7E4); } // 0xBBF4F7E4
}

namespace STREAMING
{
   static void STREAMING_REQUEST_ACTOR(Any p0, Any p1, Any p2) { invoke<Void>(0xB0A79FEE, p0, p1, p2); } // 0xB0A79FEE
   static BOOL STREAMING_IS_ACTOR_LOADED(Any p0, int p1) { return invoke<BOOL>(0x7DF72579, p0, p1); } // 0x7DF72579
   static void STREAMING_EVICT_ACTOR(Any p0) { invoke<Void>(0x6661CF89, p0); } // 0x6661CF89
   static BOOL STREAMING_IS_WORLD_LOADED() { return invoke<BOOL>(0x87B74064); } // 0x87B74064
   static BOOL _STREAMING_IS_WORLD_LOADED_2() { return invoke<BOOL>(0x943BE053); } // 0x943BE053
   static Any STREAMING_ARE_BOUNDS_LOADED(Any p0, Any p1, Any p2) { return invoke<Any>(0xC07681C1, p0, p1, p2); } // 0xC07681C1
   static void STREAMING_REQUEST_PROP(Any p0) { invoke<Void>(0x38DC1F50, p0); } // 0x38DC1F50
   static BOOL STREAMING_IS_PROP_LOADED(Any p0) { return invoke<BOOL>(0xD7F80035, p0); } // 0xD7F80035
   static void STREAMING_EVICT_PROP(Any p0) { invoke<Void>(0xA8D12960, p0); } // 0xA8D12960
   static void STREAMING_REQUEST_PROPSET(Any p0) { invoke<Void>(0xEC1F14C8, p0); } // 0xEC1F14C8
   static BOOL STREAMING_IS_PROPSET_LOADED(Any p0) { return invoke<BOOL>(0xF7D65903, p0); } // 0xF7D65903
   static void STREAMING_EVICT_PROPSET(Any p0) { invoke<Void>(0x4A5E4C13, p0); } // 0x4A5E4C13
   static void STREAMING_REQUEST_GRINGO(Any p0) { invoke<Void>(0x563E2E79, p0); } // 0x563E2E79
   static BOOL STREAMING_IS_GRINGO_LOADED(Any p0) { return invoke<BOOL>(0xA6C9DCEA, p0); } // 0xA6C9DCEA
   static void STREAMING_EVICT_GRINGO(Any p0) { invoke<Void>(0xA02B6AAE, p0); } // 0xA02B6AAE
   static void _STREAMING_GRINGO_DICT_ID(Any p0) { invoke<Void>(0x620649B4, p0); } // 0x620649B4
   static int _STREAMING_GRINGO_DICT_ID_2(Any p0) { return invoke<int>(0x67994764, p0); } // 0x67994764
   static void _STREAMING_GRINGO_DICT_ID_3(Any p0) { invoke<Void>(0x32FCA813, p0); } // 0x32FCA813
   static void STREAMING_REQUEST_SCRIPT(Any p0) { invoke<Void>(0x11E57A92, p0); } // 0x11E57A92
   static BOOL STREAMING_IS_SCRIPT_LOADED(Any p0) { return invoke<BOOL>(0xB5B4AEAD, p0); } // 0xB5B4AEAD
   static void STREAMING_EVICT_SCRIPT(Any p0) { invoke<Void>(0x570163E2, p0); } // 0x570163E2
   static void STREAMING_LOAD_ALL_REQUESTS_NOW(Any p0) { invoke<Void>(0x7B5C28F3, p0); } // 0x7B5C28F3
   static void STREAMING_LOAD_SCENE_EXT(float p0, float p1, float p2, float p3, float p4, float p5) { invoke<Void>(0xCB1E8485, p0, p1, p2, p3, p4, p5); } // 0xCB1E8485
   static void STREAMING_UNLOAD_SCENE() { invoke<Void>(0x39E69B1B); } // 0x39E69B1B
   static void _0x055EF7A3(Any p0, Any p1) { invoke<Void>(0x055EF7A3, p0, p1); } // 0x055EF7A3
   static void _0x338F85D9(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x338F85D9, p0, p1, p2, p3, p4, p5); } // 0x338F85D9
   static void _0x7D5C0C4D() { invoke<Void>(0x7D5C0C4D); } // 0x7D5C0C4D
   static int _0x5B404EDA() { return invoke<int>(0x5B404EDA); } // 0x5B404EDA
   static void _0xDF3DF05A(Any p0) { invoke<Void>(0xDF3DF05A, p0); } // 0xDF3DF05A
   static int _0x49E4EB10(Any p0) { return invoke<int>(0x49E4EB10, p0); } // 0x49E4EB10
   static int _0x5F4C08A2(Any p0) { return invoke<int>(0x5F4C08A2, p0); } // 0x5F4C08A2
   static void STREAMING_SET_CUTSCENE_MODE(Any p0) { invoke<Void>(0x83088F62, p0); } // 0x83088F62
   static void STREAMING_ENABLE_BOUNDS(Any p0) { invoke<Void>(0x0BEBB187, p0); } // 0x0BEBB187
   static void STREAMING_LOAD_BOUNDS(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x0F8FC4D0, p0, p1, p2, p3, p4); } // 0x0F8FC4D0
   static void STREAMING_LOAD_BOUNDS_EXT(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x1CD960B8, p0, p1, p2, p3, p4); } // 0x1CD960B8
   static void STREAMING_UNLOAD_BOUNDS() { invoke<Void>(0x09A67EC6); } // 0x09A67EC6
   static int _0xF7BABE84(Any p0) { return invoke<int>(0xF7BABE84, p0); } // 0xF7BABE84
   static void STREAMING_EVICT_ALL(Any p0) { invoke<Void>(0x7D432781, p0); } // 0x7D432781
   static BOOL IS_PLAYER_TELEPORTING() { return invoke<BOOL>(0x8EB0B2AD); } // 0x8EB0B2AD
   static void _0xCA99D3B4() { invoke<Void>(0xCA99D3B4); } // 0xCA99D3B4
   static void _0xE74C4851() { invoke<Void>(0xE74C4851); } // 0xE74C4851
   static void _0x6F9C399B() { invoke<Void>(0x6F9C399B); } // 0x6F9C399B
   static void STREAMING_ENABLE_FORCE_FRAGMENT_HIGH_LOD(Any p0) { invoke<Void>(0xBEABC729, p0); } // 0xBEABC729
   static void STREAMING_DISABLE_FORCE_FRAGMENT_HIGH_LOD(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xB226E8E3, p0, p1, p2, p3, p4, p5); } // 0xB226E8E3
   static int _STREAMING_FORCE_HIGH_LOD(Any p0) { return invoke<int>(0xE981992C, p0); } // 0xE981992C
   static int _STREAMING_UNFORCE_HIGH_LOD(Any p0) { return invoke<int>(0x8CC6066C, p0); } // 0x8CC6066C
   static int _STREAMING_CREATE_PERSISTENT_CHARACTER() { return invoke<int>(0x83E043A6); } // 0x83E043A6
}

namespace STRING
{
   static BOOL IS_STRING_VALID(const char* text) { return invoke<BOOL>(0xBDC61056, text); } // 0xBDC61056
   static BOOL _STRING_COMPARE(const char* string1, const char* string2) { return invoke<BOOL>(0x8218D693, string1, string2); } // 0x8218D693
   static BOOL _ARE_STRINGS_EQUAL_CLAMPED(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<BOOL>(0xEC28CA8E, p0, p1, p2, p3, p4, p5, p6); } // 0xEC28CA8E
   static Any STRING_CONTAINS_STRING(Any p0, Any p1) { return invoke<Any>(0xFCAFC819, p0, p1); } // 0xFCAFC819
   static float STRING_TO_FLOAT(const char* p0) { return invoke<float>(0x43BE70B5, p0); } // 0x43BE70B5
   static Any STRING_TO_INT(Any p0) { return invoke<Any>(0x590A8160, p0); } // 0x590A8160
   static Any STRING_TO_HASH(Any p0) { return invoke<Any>(0x84415E28, p0); } // 0x84415E28
   static Any STRING_LENGTH(Any p0) { return invoke<Any>(0x6CE4B233, p0); } // 0x6CE4B233
   static Any STRINGTABLE_LENGTH(Any p0) { return invoke<Any>(0x71D550C6, p0); } // 0x71D550C6
   static Any STRING_LOWER(Any p0) { return invoke<Any>(0x3E785560, p0); } // 0x3E785560
   static Any STRING_UPPER(Any p0) { return invoke<Any>(0xBC5B2116, p0); } // 0xBC5B2116
   static Any SET_OWNERSHIP_STRAGGLER(Any p0) { return invoke<Any>(0x346E91C2, p0); } // 0x346E91C2
   static Any STRING_NUM_TOKENS() { return invoke<Any>(0x7FB72180); } // 0x7FB72180
   static Any STRING_GET_TOKEN(Any p0) { return invoke<Any>(0xEE2791E5, p0); } // 0xEE2791E5
   static Any _TOKENIZE_STRING(Any p0) { return invoke<Any>(0x10873616, p0); } // 0x10873616
   static void SS_INIT(Any p0) { invoke<Void>(0x8785E0CE, p0); } // 0x8785E0CE
   static Any SS_REGISTER(Any p0, Any p1, Any p2) { return invoke<Any>(0xFD717A47, p0, p1, p2); } // 0xFD717A47
   static const char* SS_GET_STRING(Any p0, Any p1) { return invoke<const char*>(0x20D34AC5, p0, p1); } // 0x20D34AC5
   static Any SS_GET_STRING_ID(Any p0, Any p1) { return invoke<Any>(0xA2D27A1F, p0, p1); } // 0xA2D27A1F
   static Any _0xEC1E8210(Any p0) { return invoke<Any>(0xEC1E8210, p0); } // 0xEC1E8210
   static Any _0xBEDF7AA8(Any p0) { return invoke<Any>(0xBEDF7AA8, p0); } // 0xBEDF7AA8
   static Any SS_SET_TABLE_SIZE(Any p0, Any p1) { return invoke<Any>(0xAFFA5ABE, p0, p1); } // 0xAFFA5ABE
}

namespace STRINGTABLE
{
   static int _0xB3E44649(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0xB3E44649, p0, p1, p2, p3, p4); } // 0xB3E44649
   static void REQUEST_STRING_TABLE(const char* p0) { invoke<Void>(0x82B4DCCE, p0); } // 0x82B4DCCE
   static BOOL HAS_STRING_TABLE_LOADED(const char* p0) { return invoke<BOOL>(0x12D77EEC, p0); } // 0x12D77EEC
   static int _0x6857E514(Any p0) { return invoke<int>(0x6857E514, p0); } // 0x6857E514
}

namespace TASK
{
   static void TASK_ACTION_PERFORM(Any p0, Any p1) { invoke<Void>(0xE32F09B3, p0, p1); } // 0xE32F09B3
   static int TASK_ACTION_PERFORM_AT_POSITION(Any p0, Any p1, Any p2, float p3, float p4, float p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return invoke<int>(0x3F20B619, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0x3F20B619
   static int TASK_ACTION_PERFORM_ON_TARGET(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0xD7E582B1, p0, p1, p2, p3); } // 0xD7E582B1
   static void TASK_ANIMAL_PATROL(Any p0, Any p1) { invoke<Void>(0xF54E4D45, p0, p1); } // 0xF54E4D45
   static void TASK_ANIMAL_CIRCLE_AGGRESSIVELY(Any p0, Any p1) { invoke<Void>(0xEACE773D, p0, p1); } // 0xEACE773D
   static int TASK_ANIMAL_FOLLOW_AGGRESSIVELY(Any p0, Any p1, Any p2) { return invoke<int>(0x7ED7676D, p0, p1, p2); } // 0x7ED7676D
   static int TASK_ANIMAL_HUNT(Any p0, Any p1, Any p2) { return invoke<int>(0xD9B07798, p0, p1, p2); } // 0xD9B07798
   static int TASK_BE_DEAD(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x23AFEB8A, p0, p1, p2, p3); } // 0x23AFEB8A
   static int TASK_BE_DEAD_RANDOM(Any p0, Any p1, Any p2) { return invoke<int>(0x8EB3D852, p0, p1, p2); } // 0x8EB3D852
   static int TASK_BIRD_FLY_NEAR_COORD(Any p0, Any p1, float p2, float p3, float p4, Any p5, Any p6, Any p7, Any p8) { return invoke<int>(0x4730AC93, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x4730AC93
   static int TASK_BIRD_LAND(Any p0, Any p1) { return invoke<int>(0x525B028A, p0, p1); } // 0x525B028A
   static void TASK_BIRD_LAND_AT_COORD(Any p0, Any p1) { invoke<Void>(0xAD0E49E3, p0, p1); } // 0xAD0E49E3
   static int TASK_BIRD_SOAR(Any p0, float p1, float p2, Any p3, Any p4, Any p5) { return invoke<int>(0x2C5F5E1B, p0, p1, p2, p3, p4, p5); } // 0x2C5F5E1B
   static void TASK_BIRD_SOAR_AT_COORD(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x69CCFD7C, p0, p1, p2, p3); } // 0x69CCFD7C
   static void TASK_CROUCH(Any p0, Any p1) { invoke<Void>(0x616C803C, p0, p1); } // 0x616C803C
   static void TASK_DISMOUNT(Any p0, Any p1) { invoke<Void>(0x5DEF5C4A, p0, p1); } // 0x5DEF5C4A
   static void TASK_DIVE(Any p0, Any p1) { invoke<Void>(0xECAD08C7, p0, p1); } // 0xECAD08C7
   static int TASK_DIVEAWAYFROM(Any p0, Any p1, Any p2) { return invoke<int>(0xF1A3F362, p0, p1, p2); } // 0xF1A3F362
   static int TASK_DIVETOWARD(Any p0, Any p1, Any p2) { return invoke<int>(0x342F21D2, p0, p1, p2); } // 0x342F21D2
   static int TASK_DOOR_ACTION(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0xFDD2905C, p0, p1, p2, p3, p4); } // 0xFDD2905C
   static void TASK_DRAW_HOLSTER_WEAPON(Any p0, Any p1) { invoke<Void>(0xDB5F6B35, p0, p1); } // 0xDB5F6B35
   static void TASK_FACE_ACTOR(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x9F3B5B47, p0, p1, p2, p3); } // 0x9F3B5B47
   static void TASK_FACE_COORD(Any p0, Any p1, Any p2) { invoke<Void>(0x31B598FB, p0, p1, p2); } // 0x31B598FB
   static void TASK_FLEE_COORD(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x826D3459, p0, p1, p2, p3, p4, p5); } // 0x826D3459
   static void TASK_FLEE_ACTOR(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x2CF32A98, p0, p1, p2, p3, p4, p5, p6); } // 0x2CF32A98
   static void TASK_FLEE_ACTORSET(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0xCD5E23C3, p0, p1, p2, p3, p4, p5, p6); } // 0xCD5E23C3
   static void TASK_FOLLOW_ACTOR(Any p0, Any p1) { invoke<Void>(0x12F0911A, p0, p1); } // 0x12F0911A
   static void TASK_FOLLOW_AND_ATTACK_OBJECT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { invoke<Void>(0xDA646464, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0xDA646464
   static int TASK_FOLLOW_AND_ATTACK_OBJECT_ALONG_PATH(Any p0, Any p1, Any p2, Any p3, Any p4, float p5, float p6) { return invoke<int>(0x467D0FD5, p0, p1, p2, p3, p4, p5, p6); } // 0x467D0FD5
   static void TASK_FOLLOW_OBJECT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { invoke<Void>(0xFF3E3DCE, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 0xFF3E3DCE
   static void TASK_FOLLOW_OBJECT_ALONG_PATH(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x626C97D5, p0, p1, p2, p3, p4, p5); } // 0x626C97D5
   static void TASK_FOLLOW_OBJECT_AT_DISTANCE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x75A4E05E, p0, p1, p2, p3); }	// 0x75A4E05E
   static int TASK_FOLLOW_OBJECT_IN_FORMATION(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<int>(0xE2104FED, p0, p1, p2, p3, p4); } // 0xE2104FED
   static void TASK_FOLLOW_PATH(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x973DCC5B, p0, p1, p2, p3, p4, p5, p6); } // 0x973DCC5B
   static void TASK_FOLLOW_PATH_FROM_NEAREST_POINT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0x9591A996, p0, p1, p2, p3, p4, p5, p6); } // 0x9591A996
   static int TASK_FOLLOW_PATH_FROM_POINT() { return invoke<int>(0xCC8B2ECC); } //0xCC8B2ECC
   static void TASK_GO_NEAR_ACTORSET(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xF7B01E74, p0, p1, p2, p3); } // 0xF7B01E74
   static void TASK_GO_NEAR_COORD(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x55EC940B, p0, p1, p2, p3); } // 0x55EC940B
   static void TASK_GO_NEAR_OBJECT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x5EA4F1FE, p0, p1, p2, p3, p4, p5); } // 0x5EA4F1FE
   static void TASK_GO_TO_COORD(Any p0, Any p1, Any p2) { invoke<Void>(0x8C574832, p0, p1, p2); } // 0x8C574832
   static void TASK_GO_TO_COORD_AND_STAY(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x8636587A, p0, p1, p3); } // 0x8636587A
   static void TASK_GO_TO_COORD_NONSTOP(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xD62D6CE5, p0, p1, p2, p3); } // 0xD62D6CE5
   static void TASK_GO_TO_COORD_PRECISELY(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { invoke<Void>(0x6BDB3257, p0, p1, p2, p3, p4, p5, p6, p7); } // 0x6BDB3257
   static int TASK_GO_TO_COORD_USING_MATERIAL(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<int>(0xAA3E5851, p0, p1, p2, p3, p4); } // 0xAA3E5851
   static void TASK_GO_TO_OBJECT(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x01BACD08, p0, p1, p2, p3, p4); } // 0x01BACD08
   static int TASK_GUARD_PATROL_AUTO(Any p0, Any p1, float p2, Any p3, Any p4) { return invoke<int>(0x1AF7CE0E, p0, p1, p2, p3, p4); } // 0x1AF7CE0E
   static void TASK_GUARD_PATROL_PATH(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { invoke<Void>(0xFA5BB172, p0, p1, p2, p3, p4, p5, p6); } // 0xFA5BB172
   static void TASK_GUARD_STAND(Any p0, Any p1, Any p2) { invoke<Void>(0x99F65CC0, p0, p1, p2); } // 0x99F65CC0
   static void TASK_HIDE_AT_COVER(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xAB8B96A5, p0, p1, p2, p3, p4); } // 0xAB8B96A5
   static void TASK_HORSE_ACTION(Any p0, Any p1) { invoke<Void>(0x916FF236, p0, p1); } // 0x916FF236
   static int TASK_JUMP_OVER_OBSTRUCTION(Any p0, Any p1, float p2, float p3, float p4, float p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return invoke<int>(0x97BDA4C8, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0x97BDA4C8
   static int TASK_JUMP_TO_OBJECT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<int>(0x46A326E6, p0, p1, p2, p3, p4, p5, p6); } // 0x46A326E6
   static void TASK_KILL_CHAR(Any p0, Any p1) { invoke<Void>(0x1AE4B75B, p0, p1); } // 0x1AE4B75B
   static int TASK_LEDGE_ACTION(Any p0, Any p1, Any p2, Any p3, float p4, float p5, Any p6, Any p7, Any p8) { return invoke<int>(0x145B7C2B, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0x145B7C2B
   static void TASK_MELEE_ATTACK(Any p0, Any p1, Any p2) { invoke<Void>(0x4FEADDD9, p0, p1, p2); } // 0x4FEADDD9
   static void TASK_MOUNT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xB6131204, p0, p1, p2, p3, p4, p5); } // 0xB6131204
   static int TASK_PLAY_ANIM(Any p0) { return invoke<int>(0x5AB552C6, p0); } // 0x5AB552C6
   static void TASK_POINT_GUN_AT_COORD(Any p0, Any p1, Any p2) { invoke<Void>(0xAD3729AD, p0, p1, p2); } // 0xAD3729AD
   static void TASK_POINT_GUN_AT_OBJECT(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x95C206C2, p0, p1, p2, p3); } // 0x95C206C2
   static void TASK_RESPOND_TO_HORSE_WHISTLE(Any p0, Any p1) { invoke<Void>(0x69B924A7, p0, p1); } // 0x69B924A7
   static void TASK_SEARCH(Any p0, Any p1, Any p2) { invoke<Void>(0x4E17E039, p0, p1, p2); } // 0x4E17E039
   static void TASK_SEARCH_FOR_OBJECT(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xD9B57910, p0, p1, p3); } // 0xD9B57910
   static void TASK_SEEK_COVER_FROM_ACTOR(Any p0, Any p1) { invoke<Void>(0xE1C8A1B3, p0, p1); } // 0xE1C8A1B3
   static int TASK_SEEK_COVER_FROM_COORD(Any p0, Any p1, Any p2) { return invoke<int>(0x3B0F53F4, p0, p1, p2); } // 0x3B0F53F4
   static void TASK_SEQUENCE_PERFORM(Any p0, Any p1) { invoke<Void>(0x2DF2298C, p0, p1); } // 0x2DF2298C
   static void TASK_SEQUENCE_PERFORM_REPEATEDLY(Any p0, Any p1, Any p2) { invoke<Void>(0xA7A50E4D, p0, p1, p2); } // 0xA7A50E4D
   static void TASK_SHOOT_AT_COORD(Any p0, Any p1, Any p2) { invoke<Void>(0x601C22E3, p0, p1, p2); } // 0x601C22E3
   static void TASK_SHOOT_AT_COORD_FROM_POSITION(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x7B5FC704, p0, p1, p2, p3); } // 0x7B5FC704
   static void TASK_SHOOT_ENEMIES_FROM_ANY_COVER(Any p0, Any p1) { invoke<Void>(0x3C9875E5, p0, p1); } // 0x3C9875E5
   static void TASK_SHOOT_ENEMIES_FROM_COVER(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xCE584BCF, p0, p1, p2, p3); } // 0xCE584BCF
   static void TASK_SHOOT_ENEMIES_FROM_POSITION(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xCF8DB984, p0, p1, p2, p3); } // 0xCF8DB984
   static int TASK_SHOOT_ENEMIES_FROM_PREFERRED_COVER(Any p0, Any p1, float p2, float p3, Any p4, Any p5, Any p6) { return invoke<int>(0x1813667D, p0, p1, p2, p3, p4, p5, p6); } // 0x1813667D
   static void TASK_SHOOT_FROM_COVER(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0x506B8205, p0, p1, p2, p3, p4); } // 0x506B8205
   static void TASK_SHOOT_FROM_POSITION(Any p0, Any p1, Any p2) { invoke<Void>(0x326316DC, p0, p1, p2); } // 0x326316DC
   static int TASK_SIMPLE_BEHAVIOR() { return invoke<int>(0xDE18EDA3); } // 0xDE18EDA3
   static void TASK_STAND_STILL(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x6F80965D, p0, p1, p2, p3); } // 0x6F80965D
   static int TASK_STEALTH_ATTACK(Any p0, Any p1, Any p2) { return invoke<int>(0x86A98E99, p0, p1, p2); } // 0x86A98E99
   static void TASK_SURROUND_ACTOR(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x5DD80BEF, p0, p1, p2, p3, p4, p5); } // 0x5DD80BEF
   static void TASK_TAUNT_ACTOR(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0x9043D092, p0, p1, p2, p3, p4, p5); } // 0x9043D092
   static void TASK_TAUNT_ACTOR_IN_PLACE(Any p0, Any p1, Any p2) { invoke<Void>(0x030FB1FA, p0, p1, p2); } // 0x030FB1FA
   static int TASK_TR_ACTION(Any p0, Any p1, float p2, Any p3, Any p4) { return invoke<int>(0x1C7834B1, p0, p1, p2, p3, p4); } // 0x1C7834B1
   static int TASK_TR_ACTION_ON_ACTOR(Any p0, Any p1, Any p2, float p3, Any p4, Any p5) { return invoke<int>(0x0CFA55B6, p0, p1, p2, p3, p4, p5); } // 0x0CFA55B6
   static void TASK_USE_GRINGO(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xA0E003A7, p0, p1, p2, p3, p4); } // 0xA0E003A7
   static int TASK_USE_GRINGO_GROUP(Any p0, Any p1, float p2, Any p3, Any p4) { return invoke<int>(0x065D93BD, p0, p1, p2, p3, p4); } // 0x065D93BD
   static void TASK_USE_LASSO(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { invoke<Void>(0xC41AAF49, p0, p1, p2, p3, p4, p5); } // 0xC41AAF49
   static int TASK_USE_TURRET(Any p0, Any p1, float p2, Any p3, Any p4) { return invoke<int>(0x6484F21E, p0, p1, p2, p3, p4); } // 0x6484F21E
   static void TASK_USE_TURRET_AGAINST_COORD(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x3B8DBA13, p0, p1, p2, p3); } // 0x3B8DBA13
   static void TASK_USE_TURRET_AGAINST_OBJECT(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x49EC6A04, p0, p1, p2, p3); } // 0x49EC6A04
   static void TASK_VEHICLE_ENTER(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xB2CD5160, p0, p1, p2, p3); } // 0xB2CD5160
   static void TASK_VEHICLE_ENTER_SPECIFIC_LOCATION(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xDC087173, p0, p1, p2, p3, p4); } // 0xDC087173
   static void TASK_VEHICLE_LEAVE(Any p0) { invoke<Void>(0x6C1218A4, p0); } // 0x6C1218A4
   static void TASK_WANDER(Any p0, Any p1) { invoke<Void>(0x17BCA08E, p0, p1); } // 0x17BCA08E
   static void TASK_WANDER_IN_BOX(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x6840D3C1, p0, p1, p3); } // 0x6840D3C1
   static void TASK_WANDER_IN_VOLUME(Any p0, Any p1, Any p2) { invoke<Void>(0xA5F2BFAA, p0, p1, p2); } // 0xA5F2BFAA
   static int TASK_WARN_CHAR(Any p0, Any p1, Any p2) { return invoke<int>(0x9ABE6BC0, p0, p1, p2); } // 0x9ABE6BC0
   static void TASK_GO_NEAR_ACTOR(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0x3EB7590C, p0, p1, p3); } // 0x3EB7590C
   static int GET_TASK_STATUS(Any p0, Any p1) { return invoke<int>(0xCCE01E8A, p0, p1); } // 0xCCE01E8A
   static int _0x600A0EE4(Any p0, Any p1) { return invoke<int>(0x600A0EE4, p0, p1); } // 0x600A0EE4
   static int _0x016C6801(Any p0, Any p1) { return invoke<int>(0x016C6801, p0, p1); } // 0x016C6801
   static int _0xD062CBF6(Any p0, Any p1) { return invoke<int>(0xD062CBF6, p0, p1); } // 0xD062CBF6
   static int GET_TASK_NEXT_POINT_ON_PATH(Any p0, Any p1) { return invoke<int>(0xF726557C, p0, p1); } // 0xF726557C
   static void TASK_CLEAR(Any p0) { invoke<Void>(0x16876A25, p0); } // 0x16876A25
   static void TASK_OVERRIDE_CLEAR_MOVETYPE(Any p0) { invoke<Void>(0x9B9C8628, p0); } // 0x9B9C8628
   static void TASK_OVERRIDE_CLEAR_POSTURE(Any p0) { invoke<Void>(0x5394CF3B, p0); } // 0x5394CF3B
   static void TASK_OVERRIDE_SET_MOVETYPE(Any p0, Any p1) { invoke<Void>(0x172477F0, p0, p1); } // 0x172477F0
   static void TASK_OVERRIDE_SET_MOVESPEED_ABSOLUTE(Any p0, Any p1) { invoke<Void>(0xCE843315, p0, p1); } // 0xCE843315
   static void TASK_OVERRIDE_SET_MOVESPEED_NORMALIZED(Any p0, Any p1) { invoke<Void>(0x96F3BD31, p0, p1); } // 0x96F3BD31
   static void TASK_OVERRIDE_SET_POSTURE(Any p0, Any p1) { invoke<Void>(0x52D34567, p0, p1); } // 0x52D34567
   static void TASK_PRIORITY_SET(Any p0, Any p1) { invoke<Void>(0x3A95A656, p0, p1); } // 0x3A95A656
   static int TASK_SEQUENCE_OPEN() { return invoke<int>(0x8DA34524); } // 0x8DA34524
   static void TASK_SEQUENCE_CLOSE() { invoke<Void>(0x9EE3053B); } // 0x9EE3053B
   static void TASK_SEQUENCE_RELEASE(Any p0, Any p1) { invoke<Void>(0xB2D35E22, p0, p1); } // 0xB2D35E22
   static void SET_ACTOR_FACE_STYLE(Any p0, Any p1) { invoke<Void>(0x08654394, p0, p1); } // 0x08654394
   static void AI_SET_ENABLE_STICKUP_OVERRIDE(Any p0, Any p1) { invoke<Void>(0x1436588F, p0, p1); } // 0x1436588F
   static void AI_SET_ENABLE_HORSE_CHARGE_REACTIONS(Any p0, Any p1) { invoke<Void>(0xF3D88421, p0, p1); } // 0xF3D88421
   static void AI_SET_ENABLE_DEAD_BODY_REACTIONS(Any p0, Any p1) { invoke<Void>(0x1978C111, p0, p1); } // 0x1978C111
   static void TASK_FAILURE_MODE_SET(Any p0, Any p1) { invoke<Void>(0x26EBE467, p0, p1); } // 0x26EBE467
}

namespace TIME
{
   static Any _0x7C3D1193(Any p0) { return invoke<Any>(0x7C3D1193, p0); } // 0x7C3D1193
   static Any _0x61A2A3C(Any p0) { return invoke<Any>(0x61A2A3C, p0); } // 0x61A2A3C
   static Any GET_TOTAL_MINUTES(Any p0) { return invoke<Any>(0xC52F07A8, p0); } // 0xC52F07A8
   static Any _0x57FC0E16() { return invoke<Any>(0x57FC0E16); } // 0x57FC0E16
   static Any SET_DAY(Any p0, Any p1) { return invoke<Any>(0x0EBBDC34, p0, p1); } // 0x0EBBDC34
   static int GET_HOUR(Any time) { return invoke<int>(0x2765C37E, time); } // 0x2765C37E
   static Any GET_MINUTE(Any p0) { return invoke<Any>(0x1020BF6D, p0); } // 0x1020BF6D
   static Any GET_SECOND(Any p0) { return invoke<Any>(0xBA8077CF, p0); } // 0xBA8077CF
   static Any GET_DAY() { return invoke<Any>(0x63D13FB0); } // 0x63D13FB0
   static void ADD_TIME(Any p0, Any p1, Any p2, Any p3, Any p4) { invoke<Void>(0xBA4FEEBC, p0, p1, p2, p3, p4); } // 0xBA4FEEBC
   static Any _0x2F7CB0E3(Any p0) { return invoke<Any>(0x2F7CB0E3, p0); } // 0x2F7CB0E3
   static Any GET_TIME_OF_DAY() { return invoke<Any>(0x4E1DE7A5); } // 0x4E1DE7A5
   static float MAKE_TIME_OF_DAY(int hour, int minute, int second) { return invoke<float>(0xC09EAB6E, hour, minute, second); }
   static Any _0x0E453CF0(Any p0) { return invoke<Any>(0x0E453CF0, p0); } // 0x0E453CF0
   static Any _0x2DB3AC0F(Any p0) { return invoke<Any>(0x2DB3AC0F, p0); } // 0x2DB3AC0F
   static Any _0x9C9529D8(Any p0, Any p1) { return invoke<Any>(0x9C9529D8, p0, p1); } // 0x9C9529D8
   static Any _0x243AF970(Any p0, Any p1) { return invoke<Any>(0x243AF970, p0, p1); } // 0x243AF970
   static Any _0xD4FECCBC() { return invoke<Any>(0xD4FECCBC); } // 0xD4FECCBC
   static void SET_TIME_OF_DAY(Any p0) { invoke<Void>(0xAD03186C, p0); } // 0xAD03186C
   static Any SET_TIME_ACCELERATION() { return invoke<Any>(0xB98C7AA5); } // 0xB98C7AA5
   static Any GET_TIME_ACCELERATION() { return invoke<Any>(0xC87F16A8); } // 0xC87F16A8
   static Any SET_TIME_WARP(Any p0) { return invoke<Any>(0xD93E1BCB, p0); } // 0xD93E1BCB
   static Any _0xAF50E8A1(Any p0) { return invoke<Any>(0xAF50E8A1, p0); } // 0xAF50E8A1
}

namespace UI
{
   static int _0x97A50E69(Any p0) { return invoke<int>(0x97A50E69, p0); } // 0x97A50E69
   static void _UI_ENTER_EXCLUSIVE(const char* uilayer) { invoke<Void>(0xB1A2028A, uilayer); } // 0xB1A2028A
   static void UI_POP(const char* uiLayer) { invoke<Void>(0xBEE5CF6C, uiLayer); } // 0xBEE5CF6C
   static void UI_PUSH(const char* uiLayer) { invoke<Void>(0x97C5EFC8, uiLayer); } // 0x97C5EFC8
   static void UI_GOTO(Any p0) { invoke<Void>(0xA0159C77, p0); } // 0xA0159C77
   static void UI_EXIT(const char* uiLayer) { invoke<Void>(0x2DF89C2E, uiLayer); } // 0x2DF89C2E
   static void UI_SHOW(const char* uiLayer) { invoke<Void>(0xD1D1D467, uiLayer); } // 0xD1D1D467
   static void UI_REFRESH(const char* p0) { invoke<Void>(0xFAC3DF71, p0); } // 0xFAC3DF71
   static void UI_HIDE(const char* uiLayer) { invoke<Void>(0x7508E7F3, uiLayer); } // 0x7508E7F3
   static void UI_ENABLE(const char* uiLayer) { invoke<Void>(0xE576DCAD, uiLayer); } // 0xE576DCAD
   static void UI_DISABLE(const char* uiLayer) { invoke<Void>(0xC4532F84, uiLayer); } // 0xC4532F84
   static BOOL UI_ISACTIVE(const char* UiLayer) { return invoke<BOOL>(0xB1FDB70D, UiLayer); } // 0xB1FDB70D
   static void UI_ACTIVATE(const char* UiLayer) { invoke<Void>(0xD11BD55A, UiLayer); } // 0xD11BD55A
   static void UI_DEACTIVATE(const char* UiLayer) { invoke<const char*>(0xCA35BB5E, UiLayer); }// 0xCA35BB5E
   static void UI_EXCLUDE(const char* uiLayer) { invoke<Void>(0x4A005F2A, uiLayer); } // 0x4A005F2A
   static void UI_INCLUDE(const char* uiLayer) { invoke<Void>(0x209255AD, uiLayer); } // 0x209255AD
   static int UI_ISFOCUSED(const char* uiLayer) { return invoke<int>(0x6F2509E8, uiLayer); } // 0x6F2509E8
   static void UI_FOCUS(const char* uiLayer) { invoke<Void>(0x699CC85E, uiLayer); } // 0x699CC85E
   static void UI_UNFOCUS(const char* uiLayer) { invoke<Void>(0x0ACEA059, uiLayer); } // 0x0ACEA059
   static void UI_RESTORE(const char* uiLayer) { invoke<Void>(0x7ADB2BE7, uiLayer); } // 0x7ADB2BE7
   static void UI_SUPPRESS(const char* uiLayer) { invoke<Void>(0x182EC44A, uiLayer); } // 0x182EC44A
   static int _0xF10A56C5() { return invoke<int>(0xF10A56C5); } // 0xF10A56C5
   static int UI_GET_SELECTED_INDEX(const char* uiLayer, BOOL p1) { return invoke<int>(0x8B63A008, uiLayer, p1); } // 0x8B63A008
   static void UI_SET_STYLE(Any p0, Any p1) { invoke<Void>(0x1ECD8B18, p0, p1); } // 0x1ECD8B18
   static void UI_ADD_CHILD(Any p0, Any p1) { invoke<Void>(0x13F156A4, p0, p1); } // 0x13F156A4
   static void UI_SET_DATA(Any p0, Any p1, Any p2) { invoke<Void>(0x00B89B46, p0, p1, p2); } // 0x00B89B46
   static int UI_GET_NUM_CHILDREN(Any p0) { return invoke<int>(0xD3C7AEFA, p0); } // 0xD3C7AEFA
   static void UI_ANIM_SETUP(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xCBDE38C6, p0, p1, p2, p3); } // 0xCBDE38C6
   static void UI_ANIM_RESTART(Any p0) { invoke<Void>(0x4068D2E4, p0); } // 0x4068D2E4
   static float UI_ANIM_GET_TIME(Any p0) { return invoke<float>(0x7EB1ED99, p0); } // 0x7EB1ED99
   static int _0x1F9EE9E1(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x1F9EE9E1, p0, p1, p2, p3); } // 0x1F9EE9E1
   static void UI_SET_STRING(const char* gxtName, const char* string) { invoke<Void>(0xE457546C, gxtName, string); } // 0xE457546C
   static void UI_SET_STRING_FORMAT(const char* gxtName, const char* formatString, const char* string1, const char* string2, const char* string3) { invoke<Void>(0xEDA84121, gxtName, formatString, string1, string2, string3); } // 0xEDA84121
   static void UI_SET_MONEY(Any p0, Any p1, Any p2) { invoke<Void>(0xF71BD93A, p0, p1, p2); } // 0xF71BD93A
   static const char* UI_GET_STRING(const char* gxtEntry) { return invoke<const char*>(0xCCCFF80B, gxtEntry); } // 0xCCCFF80B
   static int  _0xBA89F5EA(Any p0, Any p1) { return invoke<int>(0xBA89F5EA, p0, p1); } // 0xBA89F5EA
   static int _0x591339B9(const char* p0, const char* p1) { return invoke<int>(0x591339B9, p0, p1); } // 0x591339B9
   static int UI_LABEL_SET_TEXT(Any p0) { return invoke<int>(0xB3FC8CB7, p0); } // 0xB3FC8CB7
   static int UI_LABEL_SET_VALUE(Any p0, Any p1) { return invoke<int>(0xDF50D8DE, p0, p1); } // 0xDF50D8DE
   static void AI_SET_SPECIAL_AREAS_TIME(Any p0, Any p1) { invoke<Void>(0xF53EB511, p0, p1); }// 0xF53EB511
   static void UI_BUTTON_SET_TEXT(Any p0, Any p1) { invoke<Void>(0x3DB16A3D, p0, p1); } // 0x3DB16A3D
   static int _0x9A56C3F3(Any p0) { return invoke<int>(0x9A56C3F3, p0); } // 0x9A56C3F3
   static int UI_TEXTURE_SET_HASH(Any p0) { return invoke<int>(0x573BEF3B, p0); } // 0x573BEF3B
   static void UI_SET_TEXT(const char* entry, const char* text) { invoke<Void>(0xC464D5DD, entry, text); } // 0xC464D5DD
   static void UI_SET_TEXT_HASH(Any p0, Any p1) { invoke<Void>(0x06FD03D2, p0, p1); } // 0x06FD03D2
   static int _0xE5D53722(Any p0, float p1) { return invoke<int>(0xE5D53722, p0, p1); } // 0xE5D53722
   static int _0xDF4627D1(Any p0, Any p1) { return invoke<int>(0xDF4627D1, p0, p1); } // 0xDF4627D1
   static int _0xD792B93B(Any p0, float p1) { return invoke<int>(0xD792B93B, p0, p1); } // 0xD792B93B
   static void UI_SET_ICON(Any p0, Any p1) { invoke<Void>(0x191BA4DF, p0, p1); } // 0x191BA4DF
   static void UI_DISABLE_INPUT(const char* uiLayer) { invoke<Void>(0x9E2C2701, uiLayer); } // 0x9E2C2701
   static int _0x9D20BDC4(Any p0) { return invoke<int>(0x9D20BDC4, p0); } // 0x9D20BDC4
   static int _0x1E732914(Any p0, Any p1) { return invoke<int>(0x1E732914, p0, p1); } // 0x1E732914
}

namespace UNK
{
   static void _0xD85BAFA8(Any p0) { invoke<Void>(0xD85BAFA8, p0); } // 0xD85BAFA8
   static void _0xEB99D1A9(Any p0, Any p1, Any p2) { invoke<Void>(0xEB99D1A9, p0, p1, p2); } // 0xEB99D1A9
   static void _0x0386C556(Any p0, Any p1, Any p2) { invoke<Void>(0x0386C556, p0, p1, p2); } // 0x0386C556
   static void _0xF63FA0A1(Any p0) { invoke<Void>(0xF63FA0A1, p0); } // 0xF63FA0A1
   static void GET_LOCKON_MISSION(Any p0, Any p1) { invoke<Void>(0xB59AD5B1, p0, p1); } // 0xB59AD5B1
   static void _0x4F64116B(Any p0) { invoke<Void>(0x4F64116B, p0); } // 0x4F64116B
   static void _0xBAD8B9A8(Any p0) { invoke<Void>(0xBAD8B9A8, p0); } // 0xBAD8B9A8
   static void _0x6CBF76AB(Any p0) { invoke<Void>(0x6CBF76AB, p0); } // 0x6CBF76AB
   static void _0xE0DD373F(Any p0) { invoke<Void>(0xE0DD373F, p0); } // 0xE0DD373F
   static void _0x3C6FE75D(Any p0, Any p1) { invoke<Void>(0x3C6FE75D, p0, p1); } // 0x3C6FE75D
   static void _0x74E7F898(Any p0, Any p1) { invoke<Void>(0x74E7F898, p0, p1); } // 0x74E7F898
   static void _0xA13D379B(Any p0, Any p1) { invoke<Void>(0xA13D379B, p0, p1); } // 0xA13D379B
   static void _0xAC72E757(Any p0, Any p1) { invoke<Void>(0xAC72E757, p0, p1); } // 0xAC72E757
   static void _0x99AFD2D1(Any p0, Any p1, Any p2) { invoke<Void>(0x99AFD2D1, p0, p1, p2); } // 0x99AFD2D1
}

namespace UNK2
{
   static int _0x9953D4FC(Any p0) { return invoke<int>(0x9953D4FC, p0); } // 0x9953D4FC
   static void _0x751809BB(Any p0) { invoke<Void>(0x751809BB, p0); } // 0x751809BB
   static void _0x25A42C69(Any p0) { invoke<Void>(0x25A42C69, p0); } // 0x25A42C69
   static void _0x40121E4F(Any p0, Any p1) { invoke<Void>(0x40121E4F, p0, p1); } // 0x40121E4F
   static void _0x86CB8CFB(Any p0) { invoke<Void>(0x86CB8CFB, p0); } // 0x86CB8CFB
   static void _0xD6AD0016(Any p0) { invoke<Void>(0xD6AD0016, p0); } // 0xD6AD0016
   static void _0xDE84B637(Any p0, Any p1) { invoke<Void>(0xDE84B637, p0, p1); } // 0xDE84B637
   static void _0x8C00C0BE(Any p0) { invoke<Void>(0x8C00C0BE, p0); } // 0x8C00C0BE
   static void _0x7CC67B30(Any p0) { invoke<Void>(0x7CC67B30, p0); } // 0x7CC67B30
   static void _0xD4ECD97D(Any p0) { invoke<Void>(0xD4ECD97D, p0); } // 0xD4ECD97D
   static void _0x826BB889(Any p0) { invoke<Void>(0x826BB889, p0); } // 0x826BB889
   static void _0x5473B93A(Any p0) { invoke<Void>(0x5473B93A, p0); } // 0x5473B93A
   static void _0x1B1EFCCB(Any p0) { invoke<Void>(0x1B1EFCCB, p0); } // 0x1B1EFCCB
}

namespace UNK3
{
   static Any _0x30402375(Any p0) { return invoke<Any>(0x30402375, p0); } // 0x30402375
   static Any _0x7922F870(Any p0) { return invoke<Any>(0x7922F870, p0); } // 0x7922F870
   static Any _0x663723A0(Any p0) { return invoke<Any>(0x663723A0, p0); } // 0x663723A0
   static Any _0x93CFB180(Any p0) { return invoke<Any>(0x93CFB180, p0); } // 0x93CFB180
   static Any _0xA1FCBA24(Any p0) { return invoke<Any>(0xA1FCBA24, p0); } // 0xA1FCBA24
   static int _0x7ED8B78C() { return invoke<int>(0x7ED8B78C); } // 0x7ED8B78C
   static Any _0xD4871BDB(Any p0) { return invoke<Any>(0xD4871BDB, p0); } // 0xD4871BDB
   static int _0xA88359B9(Any p0, Any p1) { return invoke<int>(0xA88359B9, p0, p1); } // 0xA88359B9
   static int _0xAD42EABC(Any p0, Any p1) { return invoke<int>(0xAD42EABC, p0, p1); } // 0xAD42EABC
   static Any _0xC65F6751(Any p0) { return invoke<Any>(0xC65F6751, p0); } // 0xC65F6751
   static Any _0x83CBD612(Any p0) { return invoke<Any>(0x83CBD612, p0); } // 0x83CBD612
   static Any _0x4AD2BC30(Any p0) { return invoke<Any>(0x4AD2BC30, p0); } // 0x4AD2BC30
   static Any _0xC1F9A360(Any p0) { return invoke<Any>(0xC1F9A360, p0); } // 0xC1F9A360
   static Any _0xFCD2DE48(Any p0) { return invoke<Any>(0xFCD2DE48, p0); } // 0xFCD2DE48
   static Any _0xB8F1D736(Any p0) { return invoke<Any>(0xB8F1D736, p0); } // 0xB8F1D736
   static int _0xEA86A817(Any p0) { return invoke<int>(0xEA86A817, p0); } // 0xEA86A817
   static int _0x43F59172(Any p0) { return invoke<int>(0x43F59172, p0); } // 0x43F59172
   static int _0x52D984AF(Any p0) { return invoke<int>(0x52D984AF, p0); } // 0x52D984AF
   static int _0x1D4786CF(Any p0) { return invoke<int>(0x1D4786CF, p0); } // 0x1D4786CF
   static Any _0x375BBD85(Any p0) { return invoke<Any>(0x375BBD85, p0); } // 0x375BBD85
   static Any _0x4819FB7C(Any p0) { return invoke<Any>(0x4819FB7C, p0); } // 0x4819FB7C
   static Any _0xC4F468AA(Any p0) { return invoke<Any>(0xC4F468AA, p0); } // 0xC4F468AA
   static void GAME_ESTIMATE_MOUNT(Any p0) { invoke<Void>(0xBD3A0E6D, p0); } // 0xBD3A0E6D
   static Any _0xD6BBC8AA(Any p0) { return invoke<Any>(0xD6BBC8AA, p0); } // 0xD6BBC8AA
}

namespace UNK4
{
   static void _0x77D6ABF5(Any p0, Any p1) { invoke<Void>(0x77D6ABF5, p0, p1); } // 0x77D6ABF5
   static void _0xE79F6CD4(Any p0, Any p1) { invoke<Void>(0xE79F6CD4, p0, p1); } // 0xE79F6CD4
   static int _0xFD91BE0D(Any p0) { return invoke<int>(0xFD91BE0D, p0); } // 0xFD91BE0D
   static int IN_SELECTED_PEDPATH(Any p0) { return invoke<int>(0xE2E6C722, p0); } // 0xE2E6C722
   static int _0xCE8F6304(Any p0) { return invoke<int>(0xCE8F6304, p0); } // 0xCE8F6304
   static int _0xAB32D5D9(Any p0) { return invoke<int>(0xAB32D5D9, p0); } // 0xAB32D5D9
   static void NET_GAMER_SET_TITLE(Any p0, Any p1, Any p2) { invoke<Void>(0x7BD7A465, p0, p1, p2); } // 0x7BD7A465
   static int _0x2357CA74(Any p0, float p1, float p2) { return invoke<int>(0x2357CA74, p0, p1, p2); } // 0x2357CA74
   static int _0x160E79C6(Any p0, Any p1) { return invoke<int>(0x160E79C6, p0, p1); } // 0x160E79C6
   static int _0xB5DDEF68(Any p0, float p1) { return invoke<int>(0xB5DDEF68, p0, p1); } // 0xB5DDEF68
   static int _0x34960D06(Any p0, Any p1) { return invoke<int>(0x34960D06, p0, p1); } // 0x34960D06
   static Any _0xE783219A(Any p0) { return invoke<Any>(0xE783219A, p0); } // 0xE783219A
   static void END_SCRIPTED_REQUEST(Any p0) { invoke<Void>(0x1958F478, p0); } // 0x1958F478
   static Any _0x2FB85996(Any p0) { return invoke<Any>(0x2FB85996, p0); } // 0x2FB85996
   static int _0xF34B8448(Any p0) { return invoke<int>(0xF34B8448, p0); } // 0xF34B8448
   static int _0x796E66E7(Any p0) { return invoke<int>(0x796E66E7, p0); } // 0x796E66E7
   static int _GROUP_COLOR(Any p0, Any p1) { return invoke<int>(0x650A7440, p0, p1); } // 0x650A7440
   static int _0xA0A5FF80(Any p0, Any p1) { return invoke<int>(0xA0A5FF80, p0, p1); } // 0xA0A5FF80
   static int _0x2634F265(Any p0, Any p1) { return invoke<int>(0x2634F265, p0, p1); } // 0x2634F265
   static void IS_HORSES_RELATIVE(Any p0, Any p1) { invoke<Void>(0x4A2E7533, p0, p1); } // 0x4A2E7533
   static Any _0x08D84437(Any p0) { return invoke<Any>(0x08D84437, p0); } // 0x08D84437
   static Any _0x784F04DD(Any p0) { return invoke<Any>(0x784F04DD, p0); } // 0x784F04DD
   static int _0x3DD6E36A(Any p0, Any p1) { return invoke<int>(0x3DD6E36A, p0, p1); } // 0x3DD6E36A
   static int _0xE5FE0A6A(Any p0) { return invoke<int>(0xE5FE0A6A, p0); } // 0xE5FE0A6A
   static int _0x25F8C46A(Any p0) { return invoke<int>(0x25F8C46A, p0); } // 0x25F8C46A
   static Any _0x3248D20E(Any p0) { return invoke<Any>(0x3248D20E, p0); } // 0x3248D20E
   static int _0x9DDB29B1(Any p0) { return invoke<int>(0x9DDB29B1, p0); } // 0x9DDB29B1
   static int _0x24A1B923() { return invoke<int>(0x24A1B923); } // 0x24A1B923
}

namespace VEHICLE
{
   static Vehicle GET_ACTOR_MOST_RECENT_VEHICLE(Actor actor) { return invoke<Vehicle>(0x58745E4B, actor); } // 0x58745E4B
   static BOOL IS_ACTOR_ON_TRAIN(Any p0, Any p1) { return invoke<BOOL>(0xD36E2D54, p0, p1); } // 0xD36E2D54
   static BOOL IS_ACTOR_ON_BOAT(Actor actor) { return invoke<BOOL>(0x9EE8AB59, actor); } // 0x9EE8AB59
   static BOOL IS_ACTOR_VEHICLE(Actor actor) { return invoke<BOOL>(0x9751B167, actor); } // 0x9751B167
   static Any IS_ACTOR_DRAFT_VEHICLE(Any p0) { return invoke<Any>(0x5D41D423, p0); } // 0x5D41D423
   static Any IS_ACTOR_DRIVING_VEHICLE(Any p0) { return invoke<Any>(0xDC99C124, p0); } // 0xDC99C124
   static Any _0x1BA90C92() { return invoke<Any>(0x1BA90C92); } // 0x1BA90C92
   static Any _0x12325AE7(Any p0) { return invoke<Any>(0x12325AE7, p0); } // 0x12325AE7
   static Any IS_ACTOR_RIDING_VEHICLE(Any p0, Any p1) { return invoke<Any>(0xDE19A1F9, p0, p1); } // 0xDE19A1F9
   static Vehicle GET_VEHICLE(Actor actor) { return invoke<Vehicle>(0xA0936EB6, actor); } // 0xA0936EB6
   static Any GET_ACTOR_VEHICLE_STATE(Any p0) { return invoke<Any>(0xCEA2449F, p0); } // 0xCEA2449F
   static Any _0xDAB0D820(Any p0) { return invoke<Any>(0xDAB0D820, p0); } // 0xDAB0D820
   static BOOL SET_ACTOR_IN_VEHICLE(Actor actor, Vehicle vehicle, int seatId) { return invoke<BOOL>(0x32974F99, actor, vehicle, seatId); } // 0x32974F99
   static Any GET_DRAFT_ACTOR(Any p0, Any p1) { return invoke<Any>(0x48D5121D, p0, p1); } // 0x48D5121D
   static BOOL IS_ACTOR_DRAFTED(Actor actor) { return invoke<BOOL>(0xEF2C329D, actor); } // 0xEF2C329D
   static Any GET_ACTOR_DRAFTED_TO(Any p0) { return invoke<Any>(0xD89C14BA, p0); } // 0xD89C14BA
   static Any IS_SEAT_OCCUPIED(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0xF7400A47, p0, p1, p2, p3); } // 0xF7400A47
   static Any GET_ACTOR_IN_VEHICLE_SEAT(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0xE8E94C3B, p0, p1, p2, p3, p4); } // 0xE8E94C3B
   static Any GET_NUM_AVAILABLE_SEATS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<Any>(0x3ACE659E, p0, p1, p2, p3, p4, p5, p6); } // 0x3ACE659E
   static Any _0xF0354E46(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return invoke<Any>(0xF0354E46, p0, p1, p2, p3, p4, p5, p6); } // 0xF0354E46
   static BOOL ENABLE_VEHICLE_SEAT(Actor vehicle, int seat, BOOL enable) { return invoke<BOOL>(0x6AC8234D, vehicle, seat, enable); } // 0x6AC8234D
   static void STOP_VEHICLE(Any p0) { invoke<Void>(0xC2232D29, p0); } // 0xC2232D29
   static void START_VEHICLE(Any p0) { invoke<Void>(0xE4442AB2, p0); } // 0xE4442AB2
   static Any _0xB12584C8(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return invoke<Any>(0xB12584C8, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 0xB12584C8
   static Any _GET_MAX_DRAFT_COUNT(Any p0, Any p1) { return invoke<Any>(0xD85CA776, p0, p1); } // 0xD85CA776
   static void ATTACH_DRAFT_TO_VEHICLE(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xB0A81226, p0, p1, p2, p3); } // 0xB0A81226
   static void DETACH_DRAFT_FROM_VEHICLE_BY_ACTOR(Any p0, Any p1, Any p2, Any p3) { invoke<Void>(0xF763B06D, p0, p1, p2, p3); } // 0xF763B06D
   static void DETACH_DRAFT_FROM_VEHICLE_BY_INDEX(Any p0) { invoke<Void>(0x8C3B533B, p0); } // 0x8C3B533B
   static void TRAIN_CREATE_NEW_TRAIN(Any p0) { invoke<Void>(0x8533AC9D, p0); } // 0x8533AC9D
   static void TRAIN_DESTROY_TRAIN(Any p0) { invoke<Void>(0x74CECEB3, p0); } // 0x74CECEB3
   static void TRAIN_RELEASE_TRAIN(Any p0) { invoke<Void>(0x87082991, p0); } // 0x87082991
   static void TRAIN_IS_VALID(Any p0) { invoke<Void>(0x7224CD9B, p0); } // 0x7224CD9B
   static Any _TRAIN_ADD_NEW_TRAIN_CAR_FROM_ENUM(Any p0) { return invoke<Any>(0xA7A672FA, p0); } // 0xA7A672FA
   static Any TRAIN_GET_VELOCITY(Any p0) { return invoke<Any>(0xF2373407, p0); } // 0xF2373407
   static void TRAIN_SET_TARGET_POS(Any p0) { invoke<Void>(0x9091E0A3, p0); } // 0x9091E0A3
   static void TRAIN_SET_SPEED(Any p0) { invoke<Void>(0x9D93961C, p0); } // 0x9D93961C
   static void TRAIN_SET_TARGET_SPEED(Any p0) { invoke<Void>(0xEA2A8B79, p0); } // 0xEA2A8B79
   static void TRAIN_SET_MAX_ACCEL(Any p0) { invoke<Void>(0xB5383B93, p0); } // 0xB5383B93
   static void TRAIN_SET_MAX_DECEL(Any p0) { invoke<Void>(0xB7A4D403, p0); } // 0xB7A4D403
   static void TRAIN_SET_ENGINE_ENABLED(Any p0, Any p1) { invoke<Void>(0x6C62C522, p0, p1); } // 0x6C62C522
   static Any TRAIN_GET_NUM_CARS(Any p0) { return invoke<Any>(0xFB2F9989, p0); } // 0xFB2F9989
   static void TRAIN_SET_POSITION_DIRECTION(Any p0) { invoke<Void>(0x9C488CB3, p0); } // 0x9C488CB3
   static Any _0x268D546D(Any p0) { return invoke<Any>(0x268D546D, p0); } // 0x268D546D
   static Any TRAIN_SET_FX(Any p0) { return invoke<Any>(0xBA1620AF, p0); } // 0xBA1620AF
   static Any _TRAIN_PLAY_WHISTLE(Any p0) { return invoke<Any>(0x1440C806, p0); } // 0x1440C806
   static Any TRAIN_ENABLE_VISUAL_DEBUG(Any p0) { return invoke<Any>(0x4DF9283F, p0); } // 0x4DF9283F
   static Any TRAIN_DESTROY_CAR(Any p0) { return invoke<Any>(0x2040FB19, p0); } // 0x2040FB19
   static Any TRAIN_GET_LOD_LEVEL(Any p0) { return invoke<Any>(0xD8E0EF01, p0); } // 0xD8E0EF01
   static Any TRAIN_FORCE_HIGH_LOD(Any p0) { return invoke<Any>(0x43E6DCAC, p0); } // 0x43E6DCAC
   static Any TRAIN_GET_CAR(Any p0, Any p1) { return invoke<Any>(0x41EF2EED, p0, p1); } // 0x41EF2EED
   static Any _0x7CFD539A(Any p0) { return invoke<Any>(0x7CFD539A, p0); } // 0x7CFD539A
   static Any _TRAIN_SET_AUTO_PILOT_ENABLED(Any p0, Any p1, Any p2) { return invoke<Any>(0xADE865AE, p0, p1, p2); } // 0xADE865AE
   static Any _TRAIN_SET_AUDIO_ENABLED(Any p0) { return invoke<Any>(0x6A9C8E5B, p0); } // 0x6A9C8E5B
   static Any _0x1F9F8C04(Any p0) { return invoke<Any>(0x1F9F8C04, p0); } // 0x1F9F8C04
   static Any _0xC5A04EC7(Any p0, Any p1, Any p2) { return invoke<Any>(0xC5A04EC7, p0, p1, p2); } // 0xC5A04EC7
   static Any TRAIN_GET_NEAREST_POI_DISTANCE(Any p0, Any p1, Any p2) { return invoke<Any>(0x6FC1847D, p0, p1, p2); } // 0x6FC1847D
   static Any TRAIN_GET_POSITION(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0x6D055AB, p0, p1, p2, p3); } // 0x6D055AB
   static void SET_BOAT_EXTRA_STEER(Any p0, Any p1) { invoke<Void>(0x6BB8BCFB, p0, p1); } // 0x6BB8BCFB
   static void SET_VEHICLE_ENGINE_RUNNING(Actor vehicle, BOOL running) { invoke<Void>(0x462B5FDF, vehicle, running); } // 0x462B5FDF
   static void IS_VEHICLE_ENGINE_RUNNING(Any p0, Any p1) { invoke<Void>(0x8257A916, p0, p1); } // 0x8257A916
   static void SET_VEHICLE_ALLOWED_TO_DRIVE(Actor vehicle, BOOL allowed) { invoke<Void>(0x55A56DF8, vehicle, allowed); } // 0x55A56DF8
   static void IS_VEHICLE_ALLOWED_TO_DRIVE(Any p0) { invoke<Void>(0x1C391A44, p0); } // 0x1C391A44
   static void SET_VEHICLE_PASSENGERS_ALLOWED(Any p0, Any p1) { invoke<Void>(0xBD0C1BEA, p0, p1); } // 0xBD0C1BEA
   static void SET_VEHICLE_EJECTION_ENABLED(Any p0, Any p1) { invoke<Void>(0xABD83C0, p0, p1); } // 0xABD83C0
   static void VEHICLE_SET_HANDBRAKE(Actor vehicle, BOOL handbreak) { invoke<Void>(0x384BB6AB, vehicle, handbreak); } // 0x384BB6AB
   static Any _0xF801CBD7(Any p0, Any p1, Any p2) { return invoke<Any>(0xF801CBD7, p0, p1, p2); } // 0xF801CBD7
   static Any _0x71A3F193(Any p0) { return invoke<Any>(0x71A3F193, p0); } // 0x71A3F193
   static Any _0xFB252BA9(Any p0, Any p1, Any p2) { return invoke<Any>(0xFB252BA9, p0, p1, p2); } // 0xFB252BA9
}

namespace VEHICLEWEAPON
{
   static BOOL IS_USING_TURRET(Any p0) { return invoke<BOOL>(0x2C5983E0, p0); } // 0x2C5983E0
}

namespace VOLUME
{
   static BOOL IS_VOLUME_VALID(Any p0) { return invoke<BOOL>(0xBC33CEB5, p0); } // 0xBC33CEB5
   static BOOL IS_POINT_IN_VOLUME(Any p0, Any p1, Any p2, Any p3) { return invoke<BOOL>(0xB85BB21B, p0, p1, p2, p3); } // 0xB85BB21B
   static BOOL IS_ACTOR_IN_VOLUME(Any p0, Any p1) { return invoke<BOOL>(0xF5593A78, p0, p1); } // 0xF5593A78
   static int _0x0F474297(Any p0) { return invoke<int>(0x0F474297, p0); } // 0x0F474297
   static int GET_VOLUME_CENTER(Any p0, float* p1, Any p2, Any p3) { return invoke<int>(0x6729EEFE, p0, p1, p2, p3); } // 0x6729EEFE
   static void SET_VOLUME_ENABLED(Any p0, Any p1) { invoke<Void>(0x14D5CFC3, p0, p1); } // 0x14D5CFC3
   static BOOL IS_VOLUME_ENABLED(Any p0) { return invoke<BOOL>(0x29ED6F03, p0); } // 0x29ED6F03
   static Any GET_VOLUME_HEADING(Any p0) { return invoke<Any>(0x8D5609F2, p0); } // 0x8D5609F2
   static void GET_VOLUME_SCALE(Any p0, Any p1) { invoke<Void>(0xE9C34ACC, p0, p1); } // 0xE9C34ACC
   static int _0x9FC69F27(Any p0, Any p1) { return invoke<int>(0x9FC69F27, p0, p1); } // 0x9FC69F27
   static int _0x026F7060(Any p0, Any p1, Any p2, Any p3) { return invoke<int>(0x026F7060, p0, p1, p2, p3); } // 0x026F7060
}

namespace WEAPON
{
   static int ADD_ITEM(const char* ItemName, Actor actor, Any p0) { return invoke<int>(0xBAA5D41B, ItemName, actor, p0); } //0xBAA5D41B
   static void _GIVE_ITEM_BY_CRC(Actor actor, Any p1) { invoke<Void>(0xAB2D8A68, actor, p1); } // 0xAB2D8A68
   static Any _0x7609A328() { return invoke<Any>(0x7609A328); } // 0x7609A328
   static Any GET_ITEM_COUNT(Any p0) { return invoke<Any>(0xD91ED898, p0); } // 0xD91ED898
   static Any _0x4BB2BC20(Any p0) { return invoke<Any>(0x4BB2BC20, p0); } // 0x4BB2BC20
   static Any _0xF52BA99F() { return invoke<Any>(0xF52BA99F); } // 0xF52BA99F
   static Any _0xE712FCB(Any p0) { return invoke<Any>(0xE712FCB, p0); } // 0xE712FCB
   static Any ADD_ACCESSORY(const char* p0, Any p1, Any p2) { return invoke<Any>(0x5ACC0171, p0, p1, p2); } // 0x5ACC0171
   static void _GIVE_ITEM_BY_CRC_2(Actor actor, Any p1) { invoke<Void>(0xF750D150, actor, p1); } // 0xF750D150
   static void ADD_COLLECTABLE(Actor actor, Any p1) { invoke<Void>(0xF05D1566, actor, p1); } // 0xF05D1566
   static void REMOVE_COLLECTABLE(Actor actor, Any p1) { invoke<Void>(0x5889EBB7, actor, p1); } // 0x5889EBB7
   static void READY_ITEM(const char* ItemName, Actor actor) { invoke<Void>(0x2B00A643, ItemName, actor); } // 0x2B00A643
   static Any HAS_ITEM(Any p0, Any p1) { return invoke<Any>(0xB426267D, p0, p1); } // 0xB426267D
   static Any _0xC38F697(Any p0) { return invoke<Any>(0xC38F697, p0); } // 0xC38F697
   static void DELETE_ITEM(Any p0, Any p1, Any p2) { invoke<Void>(0xEFECF4F9, p0, p1, p2); } // 0xEFECF4F9
   static void DELETE_ACCESSORY(Any p0, Any p1) { invoke<Void>(0xD6A9C9D4, p0, p1); } // 0xD6A9C9D4
   static Any _0x7BF75BCE(Any p0) { return invoke<Any>(0x7BF75BCE, p0); } // 0x7BF75BCE
   static Any _0x7F4D5AE0(Any p0) { return invoke<Any>(0x7F4D5AE0, p0); } // 0x7F4D5AE0
   static Any _0x608DCAEF(Any p0) { return invoke<Any>(0x608DCAEF, p0); } // 0x608DCAEF
   static Any _0x50C0E83F() { return invoke<Any>(0x50C0E83F); } // 0x50C0E83F
   static Any GET_ITEM_IN_HAND_EQUIPSLOT(Any p0, Any p1) { return invoke<Any>(0x3A899B0E, p0, p1); } // 0x3A899B0E
   static Any _GET_AN_EQUIP_SLOT(Any p0, Any p1) { return invoke<Any>(0x0E0EFB13, p0, p1); } // 0x0E0EFB13
   static void ACTOR_DISABLE_WEAPON_RENDER(Actor actor, Any p1) { invoke<Void>(0x5E38B33C, actor, p1); } // 0x5E38B33C
   static void ACTOR_FORCE_WEAPON_RENDER(Actor actor, Any p1) { invoke<Void>(0x1511D111, actor, p1); } // 0x1511D111
   static BOOL IS_WEAPON_DRAWN(Actor actor) { return invoke<BOOL>(0xAB5FB5AC, actor); } // 0xAB5FB5AC
   static void GIVE_WEAPON_TO_ACTOR(Actor actor, int weaponId, int ammoCount, BOOL p3, Any p4) { invoke<Void>(0x6AA0EAF2, actor, weaponId, ammoCount, p3, p4); } // 0x6AA0EAF2
   static void ACTOR_SET_NEXT_WEAPON(Any p0, Any p1, Any p2) { invoke<Void>(0xBFD6D55F, p0, p1, p2); } // 0xBFD6D55F
   static Any _0x8F4B473D() { return invoke<Any>(0x8F4B473D); } // 0x8F4B473D
   static Any _0x09950C1B(Any p0, Any p1) { return invoke<Any>(0x09950C1B, p0, p1); } // 0x09950C1B
   static Any _0x13A63AA7() { return invoke<Any>(0x13A63AA7); } // 0x13A63AA7
   static Any _0x78145528(Any p0, Any p1) { return invoke<Any>(0x78145528, p0, p1); } // 0x78145528
   static Any _0x5CAFCBD4() { return invoke<Any>(0x5CAFCBD4); } // 0x5CAFCBD4
   static Any _0x3417766E() { return invoke<Any>(0x3417766E); } // 0x3417766E
   static Any _0xCC02BBD3() { return invoke<Any>(0xCC02BBD3); } // 0xCC02BBD3
   static Any _0xA8040D70() { return invoke<Any>(0xA8040D70); } // 0xA8040D70
   static Any _0x659532FB(Any p0, Any p1) { return invoke<Any>(0x659532FB, p0, p1); } // 0x659532FB
   static Any DELETE_WEAPON_FROM_ACTOR(Any p0) { return invoke<Any>(0xCB017277, p0); } // 0xCB017277
   static Any GET_WEAPON_EQUIPPED(Any p0, Any p1) { return invoke<Any>(0x42C0FAAA, p0, p1); } // 0x42C0FAAA
   static Any _0x6262DC5E(Any p0) { return invoke<Any>(0x6262DC5E, p0); } // 0x6262DC5E
   static Any GET_WEAPON_IN_HAND(Any p0) { return invoke<Any>(0xA4B2016D, p0); } // 0xA4B2016D
   static Any _0xCDD6F94(Any p0) { return invoke<Any>(0xCDD6F94, p0); } // 0xCDD6F94
   static Any _0x612066E5(Any p0) { return invoke<Any>(0x612066E5, p0); } // 0x612066E5
   static Any _0x2776B0F5(Any p0) { return invoke<Any>(0x2776B0F5, p0); } // 0x2776B0F5
   static Any _0xFD46B231(Any p0) { return invoke<Any>(0xFD46B231, p0); } // 0xFD46B231
   static void SET_EQUIP_SLOT_ENABLED(Any p0, Any p1, Any p2) { invoke<Void>(0xE6604B39, p0, p1, p2); } // 0xE6604B39
   static Any GET_EQUIP_SLOT_ENABLED(Any p0) { return invoke<Any>(0xA3E18517, p0); } // 0xA3E18517
   static void EQUIP_ACCESSORY(Any p0, Any p1, Any p2) { invoke<Void>(0x5A80659D, p0, p1, p2); } // 0x5A80659D
   static Any _0xF7696B8B(Any p0) { return invoke<Any>(0xF7696B8B, p0); } // 0xF7696B8B
   static BOOL HAS_ACCESSORY_ENUM(Actor actor, Any p1) { return invoke<BOOL>(0x9B958A25, actor, p1); } // 0x9B958A25
   static Any _0xE094DB31() { return invoke<Any>(0xE094DB31); } // 0xE094DB31
   static Any _0x7FDDF876(Any p0, Any p1, Any p2) { return invoke<Any>(0x7FDDF876, p0, p1, p2); } // 0x7FDDF876
   static void ACTOR_SET_WEAPON_AMMO(Actor actor, int weaponId, Any p2) { invoke<Void>(0x8266C617, actor, weaponId, p2); } // 0x8266C617
   static Any _0xB008EF49(Any p0) { return invoke<Any>(0xB008EF49, p0); } // 0xB008EF49
   static BOOL ACTOR_HAS_WEAPON(Any p0, Any p1) { return invoke<BOOL>(0x0D47CFBD, p0, p1); } // 0x0D47CFBD
   static void ACTOR_ADD_WEAPON_AMMO(Actor actor, int weaponId, int ammo) { invoke<Void>(0xCC69DCC1, actor, weaponId, ammo); } // 0xCC69DCC1
   static Any ACTOR_GET_WEAPON_AMMO(Any p0, Any p1) { return invoke<Any>(0x43DEDFAE, p0, p1); } // 0x43DEDFAE
   static Any ACTOR_DISCARD_WEAPON_AMMO(Any p0) { return invoke<Any>(0xEEC81873, p0); } // 0xEEC81873
   static Any _HAS_MESH_BIT(Any p0) { return invoke<Any>(0xA091179F, p0); } // 0xA091179F
   static Any _0x17883570(Any p0) { return invoke<Any>(0x17883570, p0); } // 0x17883570
   static Any GET_WEAPON_ENUM_FOR_AMMO_ENUM(Any p0, Any p1) { return invoke<Any>(0xA8F64D32, p0, p1); } // 0xA8F64D32
   static void SET_WEAPON_GOLD(Actor actor, int weaponId, Any p2) { invoke<Void>(0xAE44869D, actor, weaponId, p2); } // 0xAE44869D
   static int GET_WEAPON_GOLD(Actor actor, int weapon) { return invoke<int>(0x6DBD1DDB, actor, weapon); } // 0x6DBD1DDB
   static Any _0x80B30545(Any p0) { return invoke<Any>(0x80B30545, p0); } // 0x80B30545
   static void FIRE_PROJECTILE(Actor actor, int weapGroup, float p2, Vector3* origin, Vector3* target) { invoke<Void>(0x195A4286, actor, weapGroup, p2, origin, target); }
   static Any _ADD_AMMO_OF_TYPE(Any p0) { return invoke<Any>(0x98B3ABFA, p0); } // 0x98B3ABFA
   static void _SET_ACTOR_AMMO_OF_TYPE(Any p0) { invoke<Void>(0x4372593E, p0); } // 0x4372593E
   static void _SET_ACTOR_MAX_AMMO_AMOUNT(Any p0, Any p1) { invoke<Void>(0x6ADAAD87, p0, p1); } // 0x6ADAAD87 
   static void _SET_ACTOR_INFINITE_AMMO_FLAG(Actor actor, int weaponGroup, BOOL toggle) { invoke<Void>(0x4FE2B586, actor, weaponGroup, toggle); } // 0x4FE2B586 
   static Any IS_FRONTEND_DEATH(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0xE224AC6F, p0, p1, p2, p3); } // 0xE224AC6F
   static Any _GET_MAX_AMMO_AMOUNT(Any p0, Any p1) { return invoke<Any>(0x7AB368CF, p0, p1); } // 0x7AB368CF
   static BOOL _GET_ACTOR_INFINITE_AMMO_FLAG(Actor actor, Any p1) { return invoke<BOOL>(0xC666B987, actor, p1); } // 0xC666B987
   static Any _0xBE39208A(Any p0) { return invoke<Any>(0xBE39208A, p0); } // 0xBE39208A
   static Any _0xBC46E3E1(Any p0, Any p1, Any p2, Any p3) { return invoke<Any>(0xBC46E3E1, p0, p1, p2, p3); } // 0xBC46E3E1
   static Any CREATE_WEAPON_PICKUP(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return invoke<Any>(0xBF0235B0, p0, p1, p2, p3, p4, p5); } // 0xBF0235B0
   static void REMOVE_ALL_PICKUPS() { invoke<Void>(0x04BF00F0); } // 0x04BF00F0
   static Any GET_NUM_WEAPONS_IN_INVENTORY() { return invoke<Any>(0x118D085E); } // 0x118D085E
   static Any _0x78A3CD3D() { return invoke<Any>(0x78A3CD3D); } // 0x78A3CD3D
   static Any _0x2C23CBE7() { return invoke<Any>(0x2C23CBE7); } // 0x2C23CBE7
   static void _REMOVE_WEAPON(Any p0) { invoke<Void>(0xD695F857, p0); } // 0xD695F857
   static Any _0x96AC812B(Any p0) { return invoke<Any>(0x96AC812B, p0); } // 0x96AC812B
   static Any _REMOVE_HAT(Any p0) { return invoke<Any>(0x5AEB2E4F, p0); } // 0x5AEB2E4F
   static Any _ADD_HAT(Any p0) { return invoke<Any>(0x3E8E7D7B, p0); } // 0x3E8E7D7B
   static Any _0x7BF01CCB() { return invoke<Any>(0x7BF01CCB); } // 0x7BF01CCB
   static Any _0x8EA46104(Any p0, Any p1, Any p2, Any p3, Any p4) { return invoke<Any>(0x8EA46104, p0, p1, p2, p3, p4); } // 0x8EA46104
   static Any _0xD2A140BC() { return invoke<Any>(0xD2A140BC); } // 0xD2A140BC
}

namespace WEAPONENUM
{
   static int _WEAPON_ENUM_PISTOL(Any p0, Any p1, Any p2) { return invoke<int>(0xBAC27559, p0, p1, p2); } // 0xBAC27559
   static int _WEAPON_ENUM_RIFLE(Any p0, Any p1, Any p2) { return invoke<int>(0xA534CD14, p0, p1, p2); } // 0xA534CD14
   static int _WEAPON_ENUM_REPEATER(Any p0, Any p1, Any p2) { return invoke<int>(0xA72B6620, p0, p1, p2); } // 0xA72B6620
   static int _WEAPON_ENUM_SNIPER_RIFLE(Any p0, Any p1, Any p2) { return invoke<int>(0x92FE3677, p0, p1, p2); } // 0x92FE3677
   static int _WEAPON_ENUM_SHOTGUN(Any p0, Any p1, Any p2) { return invoke<int>(0xEA06907B, p0, p1, p2); } // 0xEA06907B
   static int _WEAPON_ENUM_THROWN(Any p0, Any p1, Any p2) { return invoke<int>(0xE0DF7B3B, p0, p1, p2); } // 0xE0DF7B3B
   static int _WEAPON_ENUM_THROWN_EXPLODING(Any p0, Any p1, Any p2) { return invoke<int>(0xA2597101, p0, p1, p2); } // 0xA2597101
   static int _WEAPON_ENUM_BOW(Any p0, Any p1, Any p2) { return invoke<int>(0x2AD5D078, p0, p1, p2); } // 0x2AD5D078
   static int _WEAPON_ENUM_MELEE(Any p0, Any p1, Any p2) { return invoke<int>(0xA6C4E59F, p0, p1, p2); } // 0xA6C4E59F
   static int _WEAPON_ENUM_LASSO(Any p0, Any p1, Any p2) { return invoke<int>(0xF82711CC, p0, p1, p2); } // 0xF82711CC
   static int _WEAPON_ENUM_TURRET(Any p0, Any p1, Any p2) { return invoke<int>(0x82609DC7, p0, p1, p2); } // 0x82609DC7
   static int _WEAPON_ENUM_CANNON(Any p0, Any p1, Any p2) { return invoke<int>(0x628E3173, p0, p1, p2); } // 0x628E3173
   static int _0xCE5CCF2E(Any p0, Any p1) { return invoke<int>(0xCE5CCF2E, p0, p1); } // 0xCE5CCF2E
   static int _0x6A9CFA2A(Any p0) { return invoke<int>(0x6A9CFA2A, p0); } // 0x6A9CFA2A
   static const char* GET_WEAPON_DISPLAY_NAME(int weaponId) { return invoke<const char*>(0x35CD589C, weaponId); } // 0x35CD589C
   static const char* _0x87C5471F(Any p0) { return invoke<const char*>(0x87C5471F, p0); } // 0x87C5471F
   static int* _0xBE06C265(Any p0) { return invoke<int*>(0xBE06C265, p0); } // 0xBE06C265
   static int* GET_WEAPON_FRAGMENT_NAME() { return invoke<int*>(0xE8739A48); } // 0xE8739A48
   static int _0x01C7193C() { return invoke<int>(0x01C7193C); }// 0x01C7193C
   static int _0x0A23A69C() { return invoke<int>(0x0A23A69C); } // 0x0A23A69C
   static int _SET_WEAPON_ENUM_LOCKED(Any p0, Any p1) { return invoke<int>(0x0E4B7A33, p0, p1); } // 0x0E4B7A33
   static int _0xCCE4A339(Any p0) { return invoke<int>(0xCCE4A339, p0); } // 0xCCE4A339
   static int _0xDB679ED9(Any p0) { return invoke<int>(0xDB679ED9, p0); } // 0xDB679ED9
   static Any GET_AMMO_ENUM(Any p0) { return invoke<Any>(0xD3E16075, p0); } // 0xD3E16075
   static int _0x08A655C5(Any p0, float p1) { return invoke<int>(0x08A655C5, p0, p1); } // 0x08A655C5
   static const char* _0xCCB57C38(Any p0) { return invoke<const char*>(0xCCB57C38, p0); } // 0xCCB57C38
   static int _0x2AF84928(Any p0) { return invoke<int>(0x2AF84928, p0); } // 0x2AF84928
   static float GET_WEAPON_MAX_AMMO() { return invoke<float>(0xA677B204); } // 0xA677B204
   static int _0xD291A820(Any p0) { return invoke<int>(0xD291A820, p0); } // 0xD291A820
   static int _0xF4641CF4(Any p0, Any p1, float p2, float p3, float p4) { return invoke<int>(0xF4641CF4, p0, p1, p2, p3, p4); } // 0xF4641CF4
}

namespace WEATHER
{
   static void SET_WEATHER(int weatherType, float time) { invoke<Void>(0x456D7F38, weatherType, time); } // 0x456D7F38
   static Any GET_WEATHER() { return invoke<Any>(0xEA026ED9); } // 0xEA026ED9
   static void SET_WEATHER_COMPLEX(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13, Any p14) { invoke<Void>(0xC157CA40, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14); } // 0xC157CA40
   static void SET_WIND(Any p0, Any p1, Any p2) { invoke<Void>(0xC6294698, p0, p1, p2); } // 0xC6294698
   static void SET_AUTO_WIND(Any p0) { invoke<Void>(0x5D37C383, p0); } // 0x5D37C383
   static void SET_RAIN_AMOUNT(float value) { invoke<Void>(0xB788D24A, value); } // 0xB788D24A
   static Any _0xF0C9645A() { return invoke<Any>(0xF0C9645A); } // 0xF0C9645A
   static Any _0xC4C59CA4(Any p0) { return invoke<Any>(0xC4C59CA4, p0); } // 0xC4C59CA4
   static Any _0xA915DC46(Any p0) { return invoke<Any>(0xA915DC46, p0); } // 0xA915DC46
   static Any _0x9B390724(Any p0) { return invoke<Any>(0x9B390724, p0); } // 0x9B390724
   static Any _0x858FD48D(Any p0, Any p1, Any p2) { return invoke<Any>(0x858FD48D, p0, p1, p2); } // 0x858FD48D
   static void ENABLE_WEATHER_SPHERE(Any p0, Any p1) { invoke<Void>(0x17BCED9F, p0, p1); } // 0x17BCED9F
   static Any _0xFEEC4EE2() { return invoke<Any>(0xFEEC4EE2); } // 0xFEEC4EE2
   static Any _0x21A68D47(Any p0) { return invoke<Any>(0x21A68D47, p0); } // 0x21A68D47
}