#include <list>
#include <vector>
#include <string.h>
#include <pthread.h>
#include <thread>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include <stddef.h>
#include <cstdint>
#include <chrono>
#include <random>
#include <iomanip>
#include <sstream>
#include <cstdint>
#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.h"
#include "KittyMemory/MemoryPatch.h"
#include "Menu/Setup.h"

//Target lib here
#define targetLibName OBFUSCATE("libil2cpp.so")
#define targetLibNameU OBFUSCATE("libunity.so")

#include "Includes/Macros.h"

bool feature1, feature2;
void *instanceBtn;


 
bool Ping = false;


bool EnhancedKnockback = false;


bool Multihit = false;
int IsFov = 1;
int sliderValue = 1;
bool NoCooldown = false;
 



struct MemPatches
{
	MemoryPatch ai1,ai2,ai3,ai4,skillcd,invicib,
    anim,fall1,fall2,fall3,fall4,fall5,fall6,fall7,fall8,fall9,
    fall10,fall11,fall12,fall13,fall14,fall15,  
Byx, Bys, By1, By2, By3, By4,
 By5, By6, By7,
By8, By9, By10, By11,
By12, By13, By14, By15,
 By16, By17, By18, By19,
By20, By21, By22, By23,
By24, By25, By26, By27,
By28, By29, By30, By31,
By32, By33, By34, By35, By36,
 By37, By38, By39, By40,By41,
 By42, By43, By44, By45, By46, By47,
 By48,By49,By50, By51, By52, By53,
 By54, By55,By56,By57, By58, By59, By60,
 By61,By62,By63,By64,By65,By66,By67, By68,
 By69,By70, aura1,aura2,aura3,
  efc1,efc2,efc3,efc4,efc5,efc6,efc7,efc8,efc9,efc10,
    long1,long2,long3,long4,longf1,longf2,longf3,longf4,
    longs1,longs2,longs3,longs4,longw1,longw2,longw3,longw4,
    longd1,longd2,longd3,longd4,longh1,longh2,longh3,longh4,
    longb1,longb2,longb3,longb4,longx1,longx2,longx3,longx4,
    longq1,longq2,longq3,longq4,longz1,longz2,longz3,longz4,
    jmp,wnd1,wnd2,wnd3,garp1,garp2,Zoom,Speedgx0, Speedgx1, Speedgx2,
	Speedgx3,Longrangef11, Longrangeff11, Longrangefff11,Longrangeffff11,
    Longrangef12, Longrangeff12, Longrangefff12, Longrangeffff12, Longrangef13,
    Longrangeff13, Longrangefff13, Longrangeffff13, Longrangef14, Longrangeff14,
    Longrangefff14, Longrangeffff14, Longrangef15, Longrangeff15,Longrangefff15, Longrangeffff15,
     Longrangef16, Longrangeff16, Longrangefff16, Longrangeffff16, Longrangef17, Longrangeff17,
     Longrangefff17, Longrangeffff17, Longrangef18, Longrangeff18, Longrangefff18,
     Longrangeffff18, Longrangef19,Longrangeff19, Longrangefff19, Longrangeffff19,
     Longrangef20, Longrangeff20, Longrangefff20,Longrangeffff20,flag1, flag2, flag3, flag4, flag5, flag6, flag7,
flag8, flag9, flag10,flag11, flag12,flag13,flag14,
flag15,flag16,flag17,flag18,flag19,flag20,flag21,
flag22,flag23,flag24,flag25,flag26,flag27,flag28,
flag29,flag30,flag31,flag32,flag33,flag34,flag35,Fall,Wallo,canclflag,Fkdeath1,Fkdeath2,subatk0,subatk1,subatk2,flaga;

} hexPatches;


struct Vector3{float x,y,z;};


bool SamePos(const Vector3&a,const Vector3&b){
    return a.x==b.x&&a.y==b.y&&a.z==b.z;
	
}	
void (*old_CollisionSetSize)(void* collision, Vector3 size) = nullptr; 


float RandomFloat(float min, float max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}



struct ValueTuple_Float_Long {
    float Item1;
    long Item2;
};

ValueTuple_Float_Long (*old_SpeedFactor)(void *instance);
ValueTuple_Float_Long SpeedFactor(void *instance) {
    if (instance != NULL && sliderValue > 1) {
        ValueTuple_Float_Long ret;
        ValueTuple_Float_Long orig = old_SpeedFactor(instance);
        float scaled = 1.0f + ((float)(sliderValue - 1) * (9.0f / 99.0f));
        ret.Item1 = scaled; 
        ret.Item2 =  orig.Item2;                    
        return ret;
    }
    return old_SpeedFactor(instance);
}
       
void (*old_Fov)(void *instance, float value);
void Fov(void *instance, float value) {
    if (instance != NULL) {
        if (IsFov > 1) {
            old_Fov(instance, (float)IsFov);
            return;
        }
    }
    return old_Fov(instance, value);
}



struct ValueTuple_Bool_Long {
    bool Item1; // 0 = false, 1 = true
    long  Item2;
};


ValueTuple_Bool_Long (*old_CheckSameHit)(void* instance, int uniqueId, long attackHitId, float limitTime, bool isBarrier);
ValueTuple_Bool_Long my_CheckSameHit(void* instance, int uniqueId, long attackHitId, float limitTime, bool isBarrier) {
    if (instance != NULL && Multihit) {
        ValueTuple_Bool_Long ret;
        ValueTuple_Bool_Long orig = old_CheckSameHit(instance, uniqueId, attackHitId, RandomFloat(100.0f, 1000.0f), true);
        ret.Item1 = false;          // FALSE => selalu dianggap "belum kena" (allow multi hit)
        ret.Item2 = orig.Item2; // pertahankan ID/long aslinya
        return ret;
    }
 
    return old_CheckSameHit(instance, uniqueId, attackHitId, limitTime, isBarrier);
}



void (*old_AddRecord)(void* instance, int uniqueId, float limitTime, long attackHitId, bool isBarrier);
void my_AddRecord(void* instance, int uniqueId, float limitTime, long attackHitId, bool isBarrier){
    if (instance != NULL && Multihit){
        old_AddRecord(instance,uniqueId,RandomFloat(100.0f, 1000.0f),attackHitId,true);
        return;
    }
    old_AddRecord(instance,uniqueId,limitTime,attackHitId,isBarrier);
}
bool (*old_UpdateRecord)(void* instance, void* data, long attackHitId);
bool my_UpdateRecord(void* instance, void* data, long attackHitId) {
    if (instance != NULL && Multihit) {
        *(bool*)((uintptr_t)data + 0x28) = true;              // isBarrier
        *(float*)((uintptr_t)data + 0x14) = RandomFloat(100.0f, 1000.0f);
        *(float*)((uintptr_t)data + 0x18) =  RandomFloat(100.0f, 1000.0f);
        *(int*)((uintptr_t)data + 0x1C) = 6;          // hitCount
   }
   return old_UpdateRecord(instance, data, attackHitId); 
}


float (*old_GetSkillCoolTimeMax)(void* instance, int* slot, bool isStartCoolTime);
float my_GetSkillCoolTimeMax(void* instance, int* slot, bool isStartCoolTime) {
    float result = old_GetSkillCoolTimeMax(instance, slot, isStartCoolTime);
    if (instance != NULL && NoCooldown) {
        result = 0.1f;
    }
    return result;
}


typedef float (*GetPingAverage_t)(void* instance);
GetPingAverage_t orig_GetPingAverage = nullptr;

float my_GetPingAverage(void* instance) {
     if (instance != NULL && Ping) {
         return RandomFloat(1.3f, 20.0f);
     }
     return orig_GetPingAverage(instance);
}


// Extended Range 
void hk_CollisionSetSize(void* collision, Vector3 size) {
    if(EnhancedKnockback && collision){
        void* owner = *(void**)((uintptr_t)collision + 0x28);
        if(owner && size.x < 20.0f && size.z < 20.0f){
            size.x *= 20.0f;
            size.y *= 2.00f;
            size.z *= 20.0f;
        }
    }
    old_CollisionSetSize(collision, size);
}





// we wil}l run our hacks in a new thread so our while loop doesn't block process main thread
	void *hack_thread(void *) {
    LOGI(OBFUSCATE("pthread created"));


    //Check if target lib is loaded
    do {
        sleep(1);
    } while (!isLibraryLoaded(targetLibName));

    //Anti-lib rename
    /*
    do {
        sleep(1);
    } while (!isLibraryLoaded("libYOURNAME.so"));*/

    LOGI(OBFUSCATE("%s has been loaded"), (const char *) targetLibName);

#if defined(__aarch64__) //To compile this code for arm64 lib only. Do not worry about greyed out highlighting code, it still works
    
    //Playermanager
hexPatches.Byx = MemoryPatch::createWithHex("libil2cpp.so",0x17B02C0, "C0035FD6");
hexPatches.By1 = MemoryPatch::createWithHex("libil2cpp.so",0x1848F48, "C0035FD6");
hexPatches.By2 = MemoryPatch::createWithHex("libil2cpp.so",0x1A4588C, "C0035FD6");
hexPatches.By3 = MemoryPatch::createWithHex("libil2cpp.so",0x153B010, "C0035FD6");
hexPatches.By4 = MemoryPatch::createWithHex("libil2cpp.so",0x15385A8, "C0035FD6");
hexPatches.By5 = MemoryPatch::createWithHex("libil2cpp.so",0x153B41C, "C0035FD6");
hexPatches.By6 = MemoryPatch::createWithHex("libil2cpp.so",0x15385A0, "C0035FD6");
hexPatches.By7 = MemoryPatch::createWithHex("libil2cpp.so",0x1A270DC, "C0035FD6");
hexPatches.By8 = MemoryPatch::createWithHex("libil2cpp.so",0x19683FC, "C0035FD6");
hexPatches.By9 = MemoryPatch::createWithHex("libil2cpp.so",0x17B02C0, "C0035FD6");
hexPatches.By10 = MemoryPatch::createWithHex("libil2cpp.so",0x3339590, "C0035FD6");
hexPatches.By11 = MemoryPatch::createWithHex("libil2cpp.so",0x2BAFD94, "C0035FD6");
hexPatches.By12 = MemoryPatch::createWithHex("libil2cpp.so",0x34BAAA8, "C0035FD6");
hexPatches.By13 = MemoryPatch::createWithHex("libil2cpp.so",0x32DC6E8, "C0035FD6");
hexPatches.By14 = MemoryPatch::createWithHex("libil2cpp.so",0x19B1224, "C0035FD6");
hexPatches.By15 = MemoryPatch::createWithHex("libil2cpp.so",0x19AF7D8, "C0035FD6");
hexPatches.By16 = MemoryPatch::createWithHex("libil2cpp.so",0x17CDCA0, "C0035FD6");
hexPatches.By17 = MemoryPatch::createWithHex("libil2cpp.so",0x1769984, "C0035FD6");  
hexPatches.By18 = MemoryPatch::createWithHex("libil2cpp.so",0x1818A14, "C0035FD6");
hexPatches.By19 = MemoryPatch::createWithHex("libil2cpp.so",0x1818448, "C0035FD6");
hexPatches.By20 = MemoryPatch::createWithHex("libil2cpp.so",0x1818450, "C0035FD6");
hexPatches.By21 = MemoryPatch::createWithHex("libil2cpp.so",0x181F328, "C0035FD6");
hexPatches.By22 = MemoryPatch::createWithHex("libil2cpp.so",0x181D300, "C0035FD6");
hexPatches.By23 = MemoryPatch::createWithHex("libil2cpp.so",0x1835AC4, "C0035FD6");
hexPatches.By24 = MemoryPatch::createWithHex("libil2cpp.so",0x1848F5C, "C0035FD6");
hexPatches.By25 = MemoryPatch::createWithHex("libil2cpp.so",0x1848F64, "C0035FD6");
hexPatches.By26 = MemoryPatch::createWithHex("libil2cpp.so",0x1848F70, "000080D2C0035FD6");
hexPatches.By27 = MemoryPatch::createWithHex("libil2cpp.so",0x1848F78, "000080D2C0035FD6");
hexPatches.By28 = MemoryPatch::createWithHex("libil2cpp.so",0x14FF080, "000080D2C0035FD6");
hexPatches.By29 = MemoryPatch::createWithHex("libil2cpp.so",0x1842224, "000080D2C0035FD6");
hexPatches.By30 = MemoryPatch::createWithHex("libil2cpp.so",0x1842238, "000080D2C0035FD6");
hexPatches.By31 = MemoryPatch::createWithHex("libil2cpp.so", 0x125F218, "000080D2C0035FD6");
hexPatches.By32 = MemoryPatch::createWithHex("libil2cpp.so",0x1D74524, "000080D2C0035FD6");
hexPatches.By33 = MemoryPatch::createWithHex("libil2cpp.so",0x181D280, "200080D2C0035FD6");
hexPatches.By34 = MemoryPatch::createWithHex("libil2cpp.so",0x1D74524, "200080D2C0035FD6");
hexPatches.By35 = MemoryPatch::createWithHex("libil2cpp.so",0x1A4149C, "200080D2C0035FD6");
hexPatches.By36 = MemoryPatch::createWithHex("libil2cpp.so",0x199B350, "200080D2C0035FD6");
hexPatches.By37 = MemoryPatch::createWithHex("libil2cpp.so",0x1A414DC, "200080D2C0035FD6");
hexPatches.By38 = MemoryPatch::createWithHex("libil2cpp.so",0x1A418CC, "200080D2C0035FD6");
hexPatches.By39 = MemoryPatch::createWithHex("libil2cpp.so",0x1AAE370, "200080D2C0035FD6");
hexPatches.By40 = MemoryPatch::createWithHex("libil2cpp.so",0x1A41B0C, "200080D2C0035FD6");
hexPatches.By41 = MemoryPatch::createWithHex("libil2cpp.so",0x1AAC9BC, "200080D2C0035FD6");
hexPatches.By42 = MemoryPatch::createWithHex("libil2cpp.so",0x17B0948, "200080D2C0035FD6");
hexPatches.By43 = MemoryPatch::createWithHex("libil2cpp.so",0xF8B9BC, "200080D2C0035FD6");
hexPatches.By44 = MemoryPatch::createWithHex("libil2cpp.so",0xF8BEC0, "C0035FD6");
hexPatches.By45 = MemoryPatch::createWithHex("libil2cpp.so",0x1842204, "C0035FD6");
hexPatches.By46 = MemoryPatch::createWithHex("libil2cpp.so",0x17F6D74, "C0035FD6");
hexPatches.By47 = MemoryPatch::createWithHex("libil2cpp.so",0xF8F414, "C0035FD6");
hexPatches.By48 = MemoryPatch::createWithHex("libil2cpp.so",0xF8D3D4, "C0035FD6");

   
hexPatches.long1 = MemoryPatch::createWithHex("libunity.so",0xFBFB68,OBFUSCATE("0000803f"));
   hexPatches.long2 = MemoryPatch::createWithHex("libunity.so",0xFBFB64,OBFUSCATE("0000803f"));
  hexPatches.long3 = MemoryPatch::createWithHex("libunity.so",0xFBFB60,OBFUSCATE("0000803f"));
    hexPatches.long4 = MemoryPatch::createWithHex("libunity.so",0xFBFB5C,OBFUSCATE("0000803f"));    
    hexPatches.longf1 = MemoryPatch::createWithHex("libunity.so",0xFBFB68,OBFUSCATE("00000040"));
    hexPatches.longf2 = MemoryPatch::createWithHex("libunity.so",0xFBFB64,OBFUSCATE("00000040"));
    hexPatches.longf3 = MemoryPatch::createWithHex("libunity.so",0xFBFB60,OBFUSCATE("00000040"));
    hexPatches.longf4 = MemoryPatch::createWithHex("libunity.so",0xFBFB5C,OBFUSCATE("00000040"));    
    hexPatches.longs1 = MemoryPatch::createWithHex("libunity.so",0xFBFB68,OBFUSCATE("00004040"));
    hexPatches.longs2 = MemoryPatch::createWithHex("libunity.so",0xFBFB64,OBFUSCATE("00004040"));
    hexPatches.longs3 = MemoryPatch::createWithHex("libunity.so",0xFBFB60,OBFUSCATE("00004040"));
    hexPatches.longs4 = MemoryPatch::createWithHex("libunity.so",0xFBFB5C,OBFUSCATE("00004040"));    
    hexPatches.longw1 = MemoryPatch::createWithHex("libunity.so",0xFBFB68,OBFUSCATE("00008040"));
    hexPatches.longw2 = MemoryPatch::createWithHex("libunity.so",0xFBFB64,OBFUSCATE("00008040"));
    hexPatches.longw3 = MemoryPatch::createWithHex("libunity.so",0xFBFB60,OBFUSCATE("00008040"));
    hexPatches.longw4 = MemoryPatch::createWithHex("libunity.so",0xFBFB5C,OBFUSCATE("00008040"));    
    hexPatches.longd1 = MemoryPatch::createWithHex("libunity.so",0xFBFB68,OBFUSCATE("0000A040"));
    hexPatches.longd2 = MemoryPatch::createWithHex("libunity.so",0xFBFB64,OBFUSCATE("0000A040"));
    hexPatches.longd3 = MemoryPatch::createWithHex("libunity.so",0xFBFB60,OBFUSCATE("0000A040"));
    hexPatches.longd4 = MemoryPatch::createWithHex("libunity.so",0xFBFB5C,OBFUSCATE("0000A040"));    

    //Ping 
  //  A64HookFunction((void*)getAbsoluteAddress("libil2cpp.so",0x17B3FAC), (void*)GetPingAverage_t,(void**)&orig_GetPingAverage);  
    //Multi hit
  A64HookFunction((void*)getAbsoluteAddress("libil2cpp.so", 0x1985258), (void*)my_CheckSameHit,(void**)&old_CheckSameHit);  
  A64HookFunction((void*)getAbsoluteAddress("libil2cpp.so",0x198566C), (void*)my_AddRecord,(void**)&old_AddRecord);  
  A64HookFunction((void*)getAbsoluteAddress("libil2cpp.so",0x198544C), (void*)my_UpdateRecord,(void**)&old_UpdateRecord); 
    
    //IsAlive
   hexPatches.aura1 = MemoryPatch::createWithHex("libil2cpp.so",0x179C6CC,OBFUSCATE("20 00 80 D2 C0 03 5F D6"));
   //Release
   hexPatches.aura2 = MemoryPatch::createWithHex("libil2cpp.so",0x197FDF8,OBFUSCATE("20 00 80 D2 C0 03 5F D6"));
   //
   hexPatches.aura3 = MemoryPatch::createWithHex("libil2cpp.so",0x199B724,OBFUSCATE("20 00 80 D2 C0 03 5F D6"));
   //No Fall
    hexPatches.fall1 = MemoryPatch::createWithHex("libil2cpp.so",0x1993D40,OBFUSCATE("20 00 80 D2 C0 03 5F D6"));
    hexPatches.fall2 = MemoryPatch::createWithHex("libil2cpp.so",0x1993D60,OBFUSCATE("20 00 80 D2 C0 03 5F D6"));
    hexPatches.fall3 = MemoryPatch::createWithHex("libil2cpp.so",0x1993D80,OBFUSCATE("20 00 80 D2 C0 03 5F D6"));
    hexPatches.fall4 = MemoryPatch::createWithHex("libil2cpp.so",0x199DEB8,OBFUSCATE("20 00 80 D2 C0 03 5F D6"));
    hexPatches.fall5 = MemoryPatch::createWithHex("libil2cpp.so",0x199DF24,OBFUSCATE("20 00 80 D2 C0 03 5F D6"));
    hexPatches.fall6 = MemoryPatch::createWithHex("libil2cpp.so",0x199DFC4,OBFUSCATE("20 00 80 D2 C0 03 5F D6"));
    hexPatches.fall7 = MemoryPatch::createWithHex("libil2cpp.so",0x1A3F3C0,OBFUSCATE("20 00 80 D2 C0 03 5F D6"));
    hexPatches.fall8 = MemoryPatch::createWithHex("libil2cpp.so",0x1A3F3DC,OBFUSCATE("20 00 80 D2 C0 03 5F D6"));
    hexPatches.fall9 = MemoryPatch::createWithHex("libil2cpp.so",0x1A3F3F8,OBFUSCATE("20 00 80 D2 C0 03 5F D6"));
    hexPatches.fall10 = MemoryPatch::createWithHex("libil2cpp.so",0x199FF00,OBFUSCATE("20 00 80 D2 C0 03 5F D6"));
    hexPatches.fall11 = MemoryPatch::createWithHex("libil2cpp.so",0x19E8FD0,OBFUSCATE("00 00 80 D2 C0 03 5F D6"));
    hexPatches.fall12 = MemoryPatch::createWithHex("libil2cpp.so",0x1A29BFC,OBFUSCATE("20 00 80 D2 C0 03 5F D6"));
    
	//Fall unlimited
	hexPatches.Fall = MemoryPatch::createWithHex("libil2cpp.so",0x1953D08,"20 00 80 52 C0 03 5F D6");
    
    //Stop bot
    hexPatches.ai1 = MemoryPatch::createWithHex("libil2cpp.so",0x195A1A4,OBFUSCATE("20 00 80 D2 C0 03 5F D6"));
    hexPatches.ai2 = MemoryPatch::createWithHex("libil2cpp.so",0x195F680,OBFUSCATE("20 00 80 D2 C0 03 5F D6"));
    hexPatches.ai3 = MemoryPatch::createWithHex("libil2cpp.so",0x1955B00,OBFUSCATE("20 00 80 D2 C0 03 5F D6"));
    hexPatches.ai4 = MemoryPatch::createWithHex("libil2cpp.so",0x19D1790,OBFUSCATE("20 00 80 D2 C0 03 5F D6"));
    //Invicible(solo)
    hexPatches.invicib = MemoryPatch::createWithHex("libil2cpp.so",0x1993E5C,OBFUSCATE("20 00 80 D2 C0 03 5F D6"));
    //cancel effect
    //DamageNumberView
hexPatches.efc1 = MemoryPatch::createWithHex("libil2cpp.so",0x19D150C,"C0035FD6");
hexPatches.efc2 = MemoryPatch::createWithHex("libil2cpp.so",0x1A3C9C4, "C0035FD6");
hexPatches.efc3 = MemoryPatch::createWithHex("libil2cpp.so",0x1A3CD90, "C0035FD6");
hexPatches.efc4 = MemoryPatch::createWithHex("libil2cpp.so",0x3447690, "406B8512006DAA720000271EC0035FD6");
hexPatches.efc5 = MemoryPatch::createWithHex("libil2cpp.so",0x19F7CD8, "C0035FD6");
hexPatches.efc6 = MemoryPatch::createWithHex("libil2cpp.so",0x19F8158,"C0035FD6");
hexPatches.efc7 = MemoryPatch::createWithHex("libil2cpp.so",0x19FA014, "C0035FD6");
hexPatches.efc8 = MemoryPatch::createWithHex("libil2cpp.so",0x19F4AB0, "C0035FD6");
hexPatches.efc9 = MemoryPatch::createWithHex("libil2cpp.so",0x18DB948, "C0035FD6");
hexPatches.efc10 = MemoryPatch::createWithHex("libil2cpp.so",0x18DBD78, "C0035FD6");

A64HookFunction((void*)getAbsoluteAddress("libil2cpp.so", 0x34A373C), (void*)Fov,(void**)&old_Fov);

A64HookFunction((void*)getAbsoluteAddress("libil2cpp.so", 0x1A29298), (void*)SpeedFactor,(void**)&old_SpeedFactor);

A64HookFunction((void*)getAbsoluteAddress("libil2cpp.so", 0x19AB7C4), (void*)my_GetSkillCoolTimeMax,(void**)&old_GetSkillCoolTimeMax);
  ///disable jum
    hexPatches.jmp = MemoryPatch::createWithHex("libil2cpp.so",0x1A2FE40,OBFUSCATE("C0 03 5F D6"));
    //Wind
  hexPatches.wnd1 = MemoryPatch::createWithHex("libil2cpp.so",0x1A29DF4,OBFUSCATE("20 00 80 D2 C0 03 5F D6"));
    hexPatches.wnd2 = MemoryPatch::createWithHex("libil2cpp.so",0x1C19C14,OBFUSCATE("20 00 80 D2 C0 03 5F D6"));
    hexPatches.wnd3 = MemoryPatch::createWithHex("libil2cpp.so",0x19CF670,OBFUSCATE("20 00 80 D2 C0 03 5F D6"));
    //flag distance 
      hexPatches.flaga = MemoryPatch::createWithHex("libil2cpp.so", 0x19B8FB4,OBFUSCATE("20 00 80 52 C0 03 5F D6"));
      //impact
hexPatches.garp1 = MemoryPatch::createWithHex("libil2cpp.so",0x1852170,"C0035FD6");
hexPatches.garp2 = MemoryPatch::createWithHex("libil2cpp.so",0x1851E84,"C0035FD6");
//zoom
hexPatches.Zoom = MemoryPatch::createWithHex("libil2cpp.so",0x1A2FD90, "C0035FD6");
//speed game
hexPatches.Speedgx0 = MemoryPatch::createWithHex("libil2cpp.so",0x34A33C4, "4066861280B9A7720000271EC0035FD6");
hexPatches.Speedgx1 = MemoryPatch::createWithHex("libil2cpp.so",0x34A33C4, "4066861280B9A7720000271EC0035FD6");
hexPatches.Speedgx2 = MemoryPatch::createWithHex("libil2cpp.so",0x34A33C4, "A0CC8C1220E3A7720000271EC0035FD6");
hexPatches.Speedgx3 = MemoryPatch::createWithHex("libil2cpp.so",0x34A33C4, "0010211EC0035FD6");

A64HookFunction((void*)getAbsoluteAddress("libil2cpp.so", 0x179CE44), (void*)hk_CollisionSetSize, (void**)&old_CollisionSetSize);
	
    
    
#else //To compile this code for armv7 lib only.
/*
    // Hook example. Comment out if you don't use hook
    // Strings in macros are automatically obfuscated. No need to obfuscate!
    HOOK("str", FunctionExample, old_FunctionExample);
    HOOK_LIB("libFileB.so", "0x123456", FunctionExample, old_FunctionExample);
    HOOK_NO_ORIG("0x123456", FunctionExample);
    HOOK_LIB_NO_ORIG("libFileC.so", "0x123456", FunctionExample);
    HOOKSYM("__SymbolNameExample", FunctionExample, old_FunctionExample);
    HOOKSYM_LIB("libFileB.so", "__SymbolNameExample", FunctionExample, old_FunctionExample);
    HOOKSYM_NO_ORIG("__SymbolNameExample", FunctionExample);
    HOOKSYM_LIB_NO_ORIG("libFileB.so", "__SymbolNameExample", FunctionExample);

    // Patching offsets directly. Strings are automatically obfuscated too!
    PATCH("0x20D3A8", "00 00 A0 E3 1E FF 2F E1");
    PATCH_LIB("libFileB.so", "0x20D3A8", "00 00 A0 E3 1E FF 2F E1");

    //Restore changes to original
    RESTORE("0x20D3A8");
    RESTORE_LIB("libFileB.so", "0x20D3A8");

    AddMoneyExample = (void (*)(void *, int)) getAbsoluteAddress(targetLibName, 0x123456);

    LOGI(OBFUSCATE("Done"));*/
#endif

    //Anti-leech
    /*if (!iconValid || !initValid || !settingsValid) {
        //Bad function to make it crash
        sleep(5);
        int *p = 0;
        *p = 0;
    }*/

    return NULL;
}


// Do not change or translate the first text unless you know what you are doing
// Assigning feature numbers is optional. Without it, it will automatically count for you, starting from 0
// Assigned feature numbers can be like any numbers 1,3,200,10... instead in order 0,1,2,3,4,5...
// ButtonLink, Category, RichTextView and RichWebView is not counted. They can't have feature number assigned
// Toggle, ButtonOnOff and Checkbox can be switched on by default, if you add True_. Example: CheckBox_True_The Check Box
// To learn HTML, go to this page: https://www.w3schools.com/

jobjectArray GetFeatureList(JNIEnv *env, jobject context) {
    jobjectArray ret;

    const char *features[] = {
		
OBFUSCATE("98_Toggle_[🔓] FREE BYPASS"),
OBFUSCATE("88_Toggle_[🌐] PING AVERAGE"),
OBFUSCATE("66_Toggle_[💥] MULTI HIT"),
OBFUSCATE("105_Toggle_[🌟] Unlimited Gauge Skill"),
OBFUSCATE("100_CheckBox_CANCEL EFFECT"),
OBFUSCATE("3_CheckBox_NO FALL"),
OBFUSCATE("30_CheckBox_BYPASS WIND"),
OBFUSCATE("120_SeekBar_Online Long Range_1_5"),
OBFUSCATE("4_SeekBar_SPEED PLAYER_1_200"),
OBFUSCATE("90_SeekBar_FOV ME_1_120"),
OBFUSCATE("110_SeekBar_SPEED GAME_0_3"),
OBFUSCATE("106_CheckBox_Spawn Middle"),
OBFUSCATE("47_KnopfAnAus_UNLIMITED AURA"),
OBFUSCATE("144_Toggle_20X LONG RANGE"), 
OBFUSCATE("77_Toggle_STOP BOT"),
OBFUSCATE("231_Toggle_Unlimited Fall"),
OBFUSCATE("25_Toggle_INVICIBLE:"),
OBFUSCATE("33_Toggle_SKILL NO CD:"),
OBFUSCATE("20_Toggle_DISABLE JUMP"),
           
    };

    //Now you dont have to manually update the number everytime;
    int Total_Feature = (sizeof features / sizeof features[0]);
    ret = (jobjectArray)
            env->NewObjectArray(Total_Feature, env->FindClass(OBFUSCATE("java/lang/String")),
                                env->NewStringUTF(""));

    for (int i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

    return (ret);
}

void Changes(JNIEnv *env, jclass clazz, jobject obj,
                                        jint featNum, jstring featName, jint value,
                                        jboolean boolean, jstring str) {

    LOGD(OBFUSCATE("Feature name: %d - %s | Value: = %d | Bool: = %d | Text: = %s"), featNum,
         env->GetStringUTFChars(featName, 0), value,
         boolean, str != NULL ? env->GetStringUTFChars(str, 0) : "");

    //BE CAREFUL NOT TO ACCIDENTLY REMOVE break;

    
		switch (featNum) {     
        case 98:
            if (boolean){    
hexPatches.Byx.Modify();         
hexPatches.By1.Modify();       
hexPatches.By2.Modify();
hexPatches.By3.Modify();
hexPatches.By4.Modify();
hexPatches.By5.Modify();
hexPatches.By6.Modify();
hexPatches.By7.Modify();
hexPatches.By8.Modify();
hexPatches.By9.Modify();
hexPatches.By10.Modify();
hexPatches.By11.Modify();
hexPatches.By12.Modify();
hexPatches.By13.Modify();
hexPatches.By14.Modify();
hexPatches.By15.Modify();
hexPatches.By16.Modify();
hexPatches.By17.Modify();
hexPatches.By18.Modify();
hexPatches.By19.Modify();
hexPatches.By20.Modify();
hexPatches.By21.Modify();
hexPatches.By22.Modify();
hexPatches.By23.Modify();
hexPatches.By24.Modify();
hexPatches.By25.Modify();
hexPatches.By26.Modify();
hexPatches.By27.Modify();
hexPatches.By28.Modify();
hexPatches.By29.Modify();
hexPatches.By30.Modify();
hexPatches.By31.Modify();
hexPatches.By32.Modify();
hexPatches.By33.Modify();
hexPatches.By34.Modify();
hexPatches.By35.Modify();
hexPatches.By36.Modify();
hexPatches.By37.Modify();
hexPatches.By38.Modify();
hexPatches.By39.Modify();
hexPatches.By40.Modify();
hexPatches.By41.Modify();
hexPatches.By42.Modify();
hexPatches.By43.Modify();
hexPatches.By44.Modify();
hexPatches.By45.Modify();
hexPatches.By46.Modify();
hexPatches.By47.Modify();
hexPatches.By48.Modify();
	} else {
hexPatches.Byx.Restore();         
hexPatches.By1.Restore();       
hexPatches.By2.Restore();
hexPatches.By3.Restore();
hexPatches.By4.Restore();
hexPatches.By5.Restore();
hexPatches.By6.Restore();
hexPatches.By7.Restore();
hexPatches.By8.Restore();
hexPatches.By9.Restore();
hexPatches.By10.Restore();
hexPatches.By11.Restore();
hexPatches.By12.Restore();
hexPatches.By13.Restore();
hexPatches.By14.Restore();
hexPatches.By15.Restore();
hexPatches.By16.Restore();
hexPatches.By17.Restore();
hexPatches.By18.Restore();
hexPatches.By19.Restore();
hexPatches.By20.Restore();
hexPatches.By21.Restore();
hexPatches.By22.Restore();
hexPatches.By23.Restore();
hexPatches.By24.Restore();
hexPatches.By25.Restore();
hexPatches.By26.Restore();
hexPatches.By27.Restore();
hexPatches.By28.Restore();
hexPatches.By29.Restore();
hexPatches.By30.Restore();
hexPatches.By31.Restore();
hexPatches.By32.Restore();
hexPatches.By33.Restore();
hexPatches.By34.Restore();
hexPatches.By35.Restore();
hexPatches.By36.Restore();
hexPatches.By37.Restore();
hexPatches.By38.Restore();
hexPatches.By39.Restore();
hexPatches.By40.Restore();
hexPatches.By41.Restore();
hexPatches.By42.Restore();
hexPatches.By43.Restore();
hexPatches.By44.Restore();
hexPatches.By45.Restore();
hexPatches.By46.Restore();
hexPatches.By47.Restore();
hexPatches.By48.Restore();

 }
break;
        case 88:
            if (boolean){
				Ping=true;
                
	        }else{
                Ping=false;
		    }
            break;
        case 100:
            if (boolean){
                hexPatches.efc1.Modify();  
                hexPatches.efc2.Modify();  
                hexPatches.efc3.Modify();  
                hexPatches.efc4.Modify();  
                hexPatches.efc5.Modify();  
                hexPatches.efc6.Modify();  
                hexPatches.efc7.Modify();  
                hexPatches.efc8.Modify();  
                hexPatches.efc9.Modify();  
                hexPatches.efc10.Modify();  
            }else{
                hexPatches.efc1.Restore();  
                hexPatches.efc2.Restore();  
                hexPatches.efc3.Restore();  
                hexPatches.efc4.Restore();  
                hexPatches.efc5.Restore();  
                hexPatches.efc6.Restore();  
                hexPatches.efc7.Restore(); 
                hexPatches.efc8.Restore();  
                hexPatches.efc9.Restore();  
                hexPatches.efc10.Restore();  
            }
            break;
        case 3:
            if (boolean){
                hexPatches.fall1.Modify();
                hexPatches.fall2.Modify();
                hexPatches.fall3.Modify();
                hexPatches.fall4.Modify();
                hexPatches.fall5.Modify();
                hexPatches.fall6.Modify();
                hexPatches.fall7.Modify();
                hexPatches.fall8.Modify();
                hexPatches.fall9.Modify();
                hexPatches.fall10.Modify();
                hexPatches.fall11.Modify();
                hexPatches.fall12.Modify();
                
            }else{
                hexPatches.fall1.Restore();
                hexPatches.fall2.Restore();
                hexPatches.fall3.Restore();
                hexPatches.fall4.Restore();
                hexPatches.fall5.Restore();
                hexPatches.fall6.Restore();
                hexPatches.fall7.Restore();
                hexPatches.fall8.Restore();
                hexPatches.fall9.Restore();
                hexPatches.fall10.Restore();
                hexPatches.fall11.Restore();
                hexPatches.fall12.Restore();
            }
            break;
        case 4:
            sliderValue = value;
            break;
        case 66:
            if (boolean){
                Multihit=true;
                 
		    }else{
                Multihit=false;
		    }
            break;
        case 29:
            if (boolean){
               hexPatches.aura1.Modify();
            }else{
               hexPatches.aura1.Restore();     
            }
            break;
        case 47:
            if (boolean) {
               hexPatches.aura2.Modify();
               hexPatches.aura3.Modify();
            }else{
               hexPatches.aura2.Restore();
               hexPatches.aura3.Restore();
            }
            break;
        case 120:
            switch (value){
                case 0:
                    break;
                case 1:
                    hexPatches.long1.Modify();
                    hexPatches.long2.Modify();
                    hexPatches.long3.Modify();
                    hexPatches.long4.Modify();
                    break;
                case 2:
                    hexPatches.longf1.Modify();
                    hexPatches.longf2.Modify();
                    hexPatches.longf3.Modify();
                    hexPatches.longf4.Modify();
                    break;
                case 3:
                    hexPatches.longs1.Modify();
                    hexPatches.longs2.Modify();
                    hexPatches.longs3.Modify();
                    hexPatches.longs4.Modify();
                    break;
                case 4:
                    hexPatches.longw1.Modify();
                    hexPatches.longw2.Modify();
                    hexPatches.longw3.Modify();
                    hexPatches.longw4.Modify();
                    break;
                case 5:
                    hexPatches.longd1.Modify();
                    hexPatches.longd2.Modify();
                    hexPatches.longd3.Modify();
                    hexPatches.longd4.Modify();
                    break;
        }
                                   
          
            break;
        case 90:
            IsFov = value;
            break;
     
      
        case 77:
            if (boolean){
                hexPatches.ai1.Modify();
                hexPatches.ai2.Modify();
                hexPatches.ai3.Modify();
                hexPatches.ai4.Modify();
            }else{
                hexPatches.ai1.Restore();
                hexPatches.ai2.Restore();
                hexPatches.ai3.Restore();
                hexPatches.ai4.Restore();
            }
            break;
        case 25:
            if (boolean){
                hexPatches.invicib.Modify(); 
            }else{
                hexPatches.invicib.Restore();
            }
            break;
        case 33:
            if (boolean){
                NoCooldown=true;
            }else{
                NoCooldown=false;
            }
            break;
        case 20:
            if (boolean){
                hexPatches.jmp.Modify();
            }else{
                hexPatches.jmp.Restore();
            }
            break;
        case 30:
            if (boolean){
                hexPatches.wnd1.Modify();
                hexPatches.wnd2.Modify();
                hexPatches.wnd3.Modify();
            }else{
                hexPatches.wnd1.Restore();
                hexPatches.wnd2.Restore();
                hexPatches.wnd3.Restore();
            }
            break;
			case 103:
			if (boolean) {
			hexPatches.flaga.Modify();
			}else{
			hexPatches.flaga.Restore();
			
			}
			break;
			case 105:
		if (boolean) {
	hexPatches.garp1.Modify(); 
	hexPatches.garp2.Modify(); 
	} else {
	hexPatches.garp1.Restore();
	hexPatches.garp2.Restore(); 
 }
break;
case 106:
	 if (boolean) {
	hexPatches.Zoom.Modify(); 
	} else {
	hexPatches.Zoom.Restore();
 }
break;
case 110:
	switch (value) {
              case 0:
                hexPatches.Speedgx0.Restore();
                break;
                        
                case 1:
                hexPatches.Speedgx1.Modify();
                break;
                
                case 2:
                hexPatches.Speedgx2.Modify();               
                break;
                
                case 3:
                hexPatches.Speedgx3.Modify();
                break;
             
                
                   }
            break;
		
      
		case 144:
		EnhancedKnockback = boolean;
		
       break; 

	if (boolean) {
	  hexPatches.Fall.Modify();
	}else{
	  hexPatches.Fall.Restore();
	  
	  }
	  break;       
              
	
	}	
		
    
    }
	
	
__attribute__((constructor))
void lib_main() {
    // Create a new thread so it does not block the main thread, means the game would not freeze
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
}

int RegisterMenu(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {OBFUSCATE("Icon"), OBFUSCATE("()Ljava/lang/String;"), reinterpret_cast<void *>(Icon)},
            {OBFUSCATE("IconWebViewData"),  OBFUSCATE("()Ljava/lang/String;"), reinterpret_cast<void *>(IconWebViewData)},
            {OBFUSCATE("IsGameLibLoaded"),  OBFUSCATE("()Z"), reinterpret_cast<void *>(isGameLibLoaded)},
            {OBFUSCATE("Init"),  OBFUSCATE("(Landroid/content/Context;Landroid/widget/TextView;Landroid/widget/TextView;)V"), reinterpret_cast<void *>(Init)},
            {OBFUSCATE("SettingsList"),  OBFUSCATE("()[Ljava/lang/String;"), reinterpret_cast<void *>(SettingsList)},
            {OBFUSCATE("GetFeatureList"),  OBFUSCATE("()[Ljava/lang/String;"), reinterpret_cast<void *>(GetFeatureList)},
    };

    jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Menu"));
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;
    return JNI_OK;
}

int RegisterPreferences(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {OBFUSCATE("Changes"), OBFUSCATE("(Landroid/content/Context;ILjava/lang/String;IZLjava/lang/String;)V"), reinterpret_cast<void *>(Changes)},
    };
    jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Preferences"));
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;
    return JNI_OK;
}

int RegisterMain(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {OBFUSCATE("CheckOverlayPermission"), OBFUSCATE("(Landroid/content/Context;)V"), reinterpret_cast<void *>(CheckOverlayPermission)},
    };
    jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Main"));
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;

    return JNI_OK;
}

extern "C"
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    if (RegisterMenu(env) != 0)
        return JNI_ERR;
    if (RegisterPreferences(env) != 0)
        return JNI_ERR;
    if (RegisterMain(env) != 0)
        return JNI_ERR;
    return JNI_VERSION_1_6;
}
