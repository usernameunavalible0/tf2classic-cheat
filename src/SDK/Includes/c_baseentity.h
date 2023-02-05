//===========================================================================//
// 
// 
//		A base class for the client-side representation of entities.
//	
//
//===========================================================================//

#ifndef C_BASEENTITY_H
#define C_BASEENTITY_H
#ifdef _WIN32
#pragma once
#endif

class CTakeDamageInfo;
class ITraceFilter;
class CDmgAccumulator;
class CEntityMapData;
class C_BaseAnimating;
class ISave;
class IRestore;
class IPhysicsObject;
class Quaternion;
class IClientVehicle;
class CNewParticleEffect ;
class CDamageModifier;
class C_BaseCombatCharacter;
struct CollideType_t;
struct EmitSound_t;
struct FireBulletsInfo_t;
struct SolidType_t;
struct RenderGroup_t;
struct VarMapping_t;
struct ModelInstanceHandle_t;
struct ClientRenderHandle_t;

#include "icliententitylist.h"

// WARNING: Although this class extends from IClientEntity like other classes copy/pasted from SSDK, this class calls things by VFunc Indexes instead of using direct virtual calls.

//-----------------------------------------------------------------------------
// Purpose: Base client side entity object
//-----------------------------------------------------------------------------
class C_BaseEntity : public IClientEntity
{
public:

};

#endif