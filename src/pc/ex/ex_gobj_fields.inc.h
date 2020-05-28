struct ObjectNode header;
struct Object *parentObj;
struct Object *prevObj;
u32 collidedObjInteractTypes;
s16 activeFlags;
s16 numCollidedObjs;
struct Object *collidedObjs[4];
u32 oFlags;
s16 oDialogResponse;
s16 oDialogState;
u32 oUnk94;
s32 oIntangibleTimer;
f32 oPosX;
f32 oPosY;
f32 oPosZ;
f32 oVelX;
f32 oVelY;
f32 oVelZ;
f32 oForwardVel;
f32 oForwardVelS32;
f32 oUnkBC;
f32 oUnkC0;
s32 oMoveAnglePitch;
s32 oMoveAngleYaw;
s32 oMoveAngleRoll;
s32 oFaceAnglePitch;
s32 oFaceAngleYaw;
s32 oFaceAngleRoll;
s32 oGraphYOffset;
u32 oActiveParticleFlags;
f32 oGravity;
f32 oFloorHeight;
u32 oMoveFlags;
s32 oAnimState;
s32 oAngleVelPitch;
s32 oAngleVelYaw;
s32 oAngleVelRoll;
struct Animation* oAnimations;
u32 oHeldState;
f32 oWallHitboxRadius;
f32 oDragStrength;
u32 oInteractType;
s32 oInteractStatus;
s32 oBehParams2ndByte;
s32 oAction;
s32 oSubAction;
s32 oTimer;
f32 oBounciness;
f32 oDistanceToMario;
s32 oAngleToMario;
f32 oHomeX;
f32 oHomeY;
f32 oHomeZ;
f32 oFriction;
f32 oBuoyancy;
s32 oSoundStateID;
s32 oOpacity;
s32 oDamageOrCoinValue;
s32 oHealth;
s32 oBehParams;
s32 oPrevAction;
u32 oInteractionSubtype;
f32 oCollisionDistance;
s32 oNumLootCoins;
f32 oDrawingDistance;
s32 oRoom;
u32 oUnk1A8;
s32 oWallAngle;
s16 oFloorType;
s16 oFloorRoom;
s32 oAngleToHome;
struct Surface* oFloor;
s32 oDeathSound;
void* oPathedWaypointsS16;
struct Waypoint* oPathedStartWaypoint;
struct Waypoint* oPathedPrevWaypoint;
s32 oPathedPrevWaypointFlags;
s32 oPathedTargetPitch;
s32 oPathedTargetYaw;
f32 oMacroUnk108;
f32 oMacroUnk10C;
f32 oMacroUnk110;
const BehaviorScript *curBhvCommand;
u32 bhvStackIndex;
uintptr_t bhvStack[8];
s16 bhvDelayTimer;
s16 respawnInfoType;
f32 hitboxRadius;
f32 hitboxHeight;
f32 hurtboxRadius;
f32 hurtboxHeight;
f32 hitboxDownOffset;
const BehaviorScript *behavior;
u32 unused2;
struct Object *platform;
void *collisionData;
Mat4 transform;
void *respawnInfo;