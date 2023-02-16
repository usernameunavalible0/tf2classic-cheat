#pragma once
#include "vector.h"

enum StereoEye_t
{
	STEREO_EYE_MONO = 0,
	STEREO_EYE_LEFT = 1,
	STEREO_EYE_RIGHT = 2,
	STEREO_EYE_MAX = 3,
};

struct Rect_t { int x, y, w, h; };

enum EObserverModes
{
	OBS_MODE_NONE = 0,		// not in spectator mode
	OBS_MODE_DEATHCAM,		// special mode for death cam animation
	OBS_MODE_FREEZECAM,		// zooms to a target, and freeze-frames on them
	OBS_MODE_FIXED,			// view from a fixed camera position
	OBS_MODE_FIRSTPERSON,	// follow a player in first person view
	OBS_MODE_THIRDPERSON,	// follow a player in third person view
	OBS_MODE_ROAMING,		// free roaming
};

enum
{
	TF_CLASS_UNDEFINED = 0,

	TF_CLASS_SCOUT,			// TF_FIRST_NORMAL_CLASS
	TF_CLASS_SNIPER,
	TF_CLASS_SOLDIER,
	TF_CLASS_DEMOMAN,
	TF_CLASS_MEDIC,
	TF_CLASS_HEAVYWEAPONS,
	TF_CLASS_PYRO,
	TF_CLASS_SPY,
	TF_CLASS_ENGINEER,		// TF_LAST_NORMAL_CLASS

	// Add any new classes after Engineer.
	// The following classes are not available in normal play.
	TF_CLASS_CIVILIAN,
	TF_CLASS_MERCENARY,
	TF_CLASS_COUNT_ALL,

	TF_CLASS_RANDOM
};

// Most of these conds aren't actually implemented but putting them here for compatibility.
enum
{
	TF_COND_AIMING = 0,		// Sniper aiming, Heavy minigun.
	TF_COND_ZOOMED,
	TF_COND_DISGUISING,
	TF_COND_DISGUISED,
	TF_COND_STEALTHED,
	TF_COND_INVULNERABLE,
	TF_COND_TELEPORTED,
	TF_COND_TAUNTING,
	TF_COND_INVULNERABLE_WEARINGOFF,
	TF_COND_STEALTHED_BLINK,
	TF_COND_SELECTED_TO_TELEPORT,
	TF_COND_CRITBOOSTED,
	TF_COND_TMPDAMAGEBONUS,
	TF_COND_FEIGN_DEATH,
	TF_COND_PHASE,
	TF_COND_STUNNED,
	TF_COND_OFFENSEBUFF,
	TF_COND_SHIELD_CHARGE,
	TF_COND_DEMO_BUFF,
	TF_COND_ENERGY_BUFF,
	TF_COND_RADIUSHEAL,
	TF_COND_HEALTH_BUFF,
	TF_COND_BURNING,
	TF_COND_HEALTH_OVERHEALED,
	TF_COND_URINE,
	TF_COND_BLEEDING,
	TF_COND_DEFENSEBUFF,
	TF_COND_MAD_MILK,
	TF_COND_MEGAHEAL,
	TF_COND_REGENONDAMAGEBUFF,
	TF_COND_MARKEDFORDEATH,
	TF_COND_NOHEALINGDAMAGEBUFF,
	TF_COND_SPEED_BOOST,
	TF_COND_CRITBOOSTED_PUMPKIN,
	TF_COND_CRITBOOSTED_USER_BUFF,
	TF_COND_CRITBOOSTED_DEMO_CHARGE,
	TF_COND_SODAPOPPER_HYPE,
	TF_COND_CRITBOOSTED_FIRST_BLOOD,
	TF_COND_CRITBOOSTED_BONUS_TIME,
	TF_COND_CRITBOOSTED_CTF_CAPTURE,
	TF_COND_CRITBOOSTED_ON_KILL,
	TF_COND_CANNOT_SWITCH_FROM_MELEE,
	TF_COND_DEFENSEBUFF_NO_CRIT_BLOCK,
	TF_COND_REPROGRAMMED,
	TF_COND_CRITBOOSTED_RAGE_BUFF,
	TF_COND_DEFENSEBUFF_HIGH,
	TF_COND_SNIPERCHARGE_RAGE_BUFF,
	TF_COND_DISGUISE_WEARINGOFF,
	TF_COND_MARKEDFORDEATH_SILENT,
	TF_COND_DISGUISED_AS_DISPENSER,
	TF_COND_SAPPED,
	TF_COND_INVULNERABLE_HIDE_UNLESS_DAMAGE,
	TF_COND_INVULNERABLE_USER_BUFF,
	TF_COND_HALLOWEEN_BOMB_HEAD,
	TF_COND_HALLOWEEN_THRILLER,
	TF_COND_RADIUSHEAL_ON_DAMAGE,
	TF_COND_CRITBOOSTED_CARD_EFFECT,
	TF_COND_INVULNERABLE_CARD_EFFECT,
	TF_COND_MEDIGUN_UBER_BULLET_RESIST,
	TF_COND_MEDIGUN_UBER_BLAST_RESIST,
	TF_COND_MEDIGUN_UBER_FIRE_RESIST,
	TF_COND_MEDIGUN_SMALL_BULLET_RESIST,
	TF_COND_MEDIGUN_SMALL_BLAST_RESIST,
	TF_COND_MEDIGUN_SMALL_FIRE_RESIST,
	TF_COND_STEALTHED_USER_BUFF,
	TF_COND_MEDIGUN_DEBUFF,
	TF_COND_STEALTHED_USER_BUFF_FADING,
	TF_COND_BULLET_IMMUNE,
	TF_COND_BLAST_IMMUNE,
	TF_COND_FIRE_IMMUNE,
	TF_COND_PREVENT_DEATH,
	TF_COND_MVM_BOT_STUN_RADIOWAVE,
	TF_COND_HALLOWEEN_SPEED_BOOST,
	TF_COND_HALLOWEEN_QUICK_HEAL,
	TF_COND_HALLOWEEN_GIANT,
	TF_COND_HALLOWEEN_TINY,
	TF_COND_HALLOWEEN_IN_HELL,
	TF_COND_HALLOWEEN_GHOST_MODE,
	TF_COND_MINICRITBOOSTED_ON_KILL,
	TF_COND_OBSCURED_SMOKE,
	TF_COND_PARACHUTE_DEPLOYED,
	TF_COND_BLASTJUMPING,
	TF_COND_HALLOWEEN_KART,
	TF_COND_HALLOWEEN_KART_DASH,
	TF_COND_BALLOON_HEAD,
	TF_COND_MELEE_ONLY,
	TF_COND_SWIMMING_CURSE,
	TF_COND_FREEZE_INPUT,
	TF_COND_HALLOWEEN_KART_CAGE,
	TF_COND_DONOTUSE_0,
	TF_COND_RUNE_STRENGTH,
	TF_COND_RUNE_HASTE,
	TF_COND_RUNE_REGEN,
	TF_COND_RUNE_RESIST,
	TF_COND_RUNE_VAMPIRE,
	TF_COND_RUNE_WARLOCK,
	TF_COND_RUNE_PRECISION,
	TF_COND_RUNE_AGILITY,
	TF_COND_GRAPPLINGHOOK,
	TF_COND_GRAPPLINGHOOK_SAFEFALL,
	TF_COND_GRAPPLINGHOOK_LATCHED,
	TF_COND_GRAPPLINGHOOK_BLEEDING,
	TF_COND_AFTERBURN_IMMUNE,
	TF_COND_RUNE_KNOCKOUT,
	TF_COND_RUNE_IMBALANCE,
	TF_COND_CRITBOOSTED_RUNE_TEMP,
	TF_COND_PASSTIME_INTERCEPTION,

	// Add TF2C conds here
	TF_COND_SMOKE_BOMB,
	TF_COND_SLOWED,
	TF_COND_INVULNERABLE_SPAWN_PROTECT,

	// Powerup conditions
	TF_COND_POWERUP_CRITDAMAGE,
	TF_COND_POWERUP_SHIELD,
	TF_COND_POWERUP_SPEEDBOOST,
	TF_COND_POWERUP_CLOAK,
	TF_COND_POWERUP_RAGEMODE,

	TF_COND_LAST
};


class VMatrix {
private:
	Vector m[4][4];

public:
	const matrix3x4_t& As3x4() const {
		return *((const matrix3x4_t*)this);
	}
};

struct PlayerInfo_t
{
	// scoreboard information
	char			name[32];
	// local server user ID, unique while server is running
	int				userID;
	// global unique player identifer
	char			guid[32 + 1];
	// friends identification number
	unsigned int		friendsID;
	// friends name
	char			friendsName[32];
	// true, if player is a bot controlled by game.dll
	bool			fakeplayer;
	// true if player is the HLTV proxy
	bool			ishltv;
	// custom files CRC for this player
	unsigned long	customFiles[4];
	// this counter increases each time the server downloaded a new file
	unsigned char	filesDownloaded;
};

class CViewSetup
{
public:
	// left side of view window
	int			x;
	int			m_nUnscaledX;
	// top side of view window
	int			y;
	int			m_nUnscaledY;
	// width of view window
	int			width;
	int			m_nUnscaledWidth;
	// height of view window
	int			height;
	// which eye are we rendering?
	StereoEye_t m_eStereoEye;
	int			m_nUnscaledHeight;

	// the rest are only used by 3D views

		// Orthographic projection?
	bool		m_bOrtho;
	// View-space rectangle for ortho projection.
	float		m_OrthoLeft;
	float		m_OrthoTop;
	float		m_OrthoRight;
	float		m_OrthoBottom;

	// horizontal FOV in degrees
	float		fov;
	// horizontal FOV in degrees for in-view model
	float		fovViewmodel;

	// 3D origin of camera
	Vector		origin;

	// heading of camera (pitch, yaw, roll)
	Vector		angles;
	// local Z coordinate of near plane of camera
	float		zNear;
	// local Z coordinate of far plane of camera
	float		zFar;

	// local Z coordinate of near plane of camera ( when rendering view model )
	float		zNearViewmodel;
	// local Z coordinate of far plane of camera ( when rendering view model )
	float		zFarViewmodel;

	// set to true if this is to draw into a subrect of the larger screen
	// this really is a hack, but no more than the rest of the way this class is used
	bool		m_bRenderToSubrectOfLargerScreen;

	// The aspect ratio to use for computing the perspective projection matrix
	// (0.0f means use the viewport)
	float		m_flAspectRatio;

	// Controls for off-center projection (needed for poster rendering)
	bool		m_bOffCenter;
	float		m_flOffCenterTop;
	float		m_flOffCenterBottom;
	float		m_flOffCenterLeft;
	float		m_flOffCenterRight;

	// Control that the SFM needs to tell the engine not to do certain post-processing steps
	bool		m_bDoBloomAndToneMapping;

	// Cached mode for certain full-scene per-frame varying state such as sun entity coverage
	bool		m_bCacheFullSceneState;

	// If using VR, the headset calibration will feed you a projection matrix per-eye.
	// This does NOT override the Z range - that will be set up as normal (i.e. the values in this matrix will be ignored).
	bool        m_bViewToProjectionOverride;
	VMatrix     m_ViewToProjection;
};

struct mstudiobbox_t
{
	int bone;
	int group;
	Vector bbmin;
	Vector bbmax;
	int szhitboxnameindex;
	int unused[8];

	const char* pszHitboxName()
	{
		if (szhitboxnameindex == 0)
			return "";

		return ((const char*)this) + szhitboxnameindex;
	}
};

struct mstudiohitboxset_t
{
	int sznameindex;
	inline char* const	pszName(void) const { return ((char*)this) + sznameindex; }
	int numhitboxes;
	int hitboxindex;
	inline mstudiobbox_t* pHitbox(int i) const { return (mstudiobbox_t*)(((unsigned char*)this) + hitboxindex) + i; };
};

struct studiohdr_t
{
	unsigned char		pad00[12];
	char				name[64];
	unsigned char		pad01[80];
	int					numbones;
	int					boneindex;
	unsigned char		pad02[12];
	int					hitboxsetindex;
	unsigned char		pad03[228];

	mstudiohitboxset_t* pHitboxSet(int i) const
	{
		return (mstudiohitboxset_t*)(((unsigned char*)this) + hitboxsetindex) + i;
	};

	inline mstudiobbox_t* pHitbox(int i, int set) const
	{
		mstudiohitboxset_t const* s = pHitboxSet(set);
		if (!s)
			return NULL;

		return s->pHitbox(i);
	};

	inline int iHitboxCount(int set) const
	{
		mstudiohitboxset_t const* s = pHitboxSet(set);
		if (!s)
			return 0;

		return s->numhitboxes;
	};
};

enum ETFClassIds
{
	CTFUmbrella = 212,
	CTFTranq = 211,
	CTFTaser = 208,
	CTFNailgun = 182,
	CTFWeaponMirv = 220,
	CTFHunterRifle = 177,
	CTFGrenadeMirvBomb = 173,
	CTFGrenadeMirvProjectile = 174,
	CTFCoilGun = 164,
	CTFAAGun = 155,
	CTFWeaponBaseMelee = 216,
	CTFWeaponBaseGun = 215,
	CTFWeaponBase = 214,
	CTFWrench = 227,
	CTFSyringeGun = 207,
	CSniperDot = 95,
	CTFSniperRifle = 206,
	CTFSMG = 205,
	CTFShovel = 204,
	CTFScatterGun = 199,
	CTFShotgun_Pyro = 202,
	CTFShotgun_HWG = 201,
	CTFShotgun_Soldier = 203,
	CTFShotgun = 200,
	CTFRocketLauncher = 198,
	CTFRevolver = 197,
	CTFPistol_Scout = 186,
	CTFPistol = 185,
	CTFPipebombLauncher = 184,
	CTFWeaponPDA_Spy = 224,
	CTFWeaponPDA_Engineer_Destroy = 223,
	CTFWeaponPDA_Engineer_Build = 222,
	CTFWeaponPDA = 221,
	CTFMinigun = 181,
	CWeaponMedigun = 232,
	CTFLunchBox = 180,
	CTFKnife = 179,
	CTFWeaponInvis = 219,
	CTFGrenadeLauncher = 172,
	CTFFlareGun = 169,
	CTFFlameThrower = 168,
	CTFFists = 167,
	CTFFireAxe = 166,
	CTFWeaponCubemap = 218,
	CTFCompoundBow = 165,
	CTFClub = 163,
	CTFBottle = 162,
	CTFBonesaw = 161,
	CTFBat = 160,
	CTFWearable = 226,
	CTFBaseRocket = 159,
	CTFBaseGrenade = 157,
	CTFGrenadeStickybombProjectile = 176,
	CTFGrenadePipebombProjectile = 175,
	CTFViewModel = 213,
	CTeamRoundTimer = 103,
	CTFRandomizerManagerProxy = 196,
	CTFProjectile_Flare = 192,
	CTFProjectile_Dart = 191,
	CTFProjectile_Coil = 190,
	CBaseObjectUpgrade = 10,
	CTFItem = 178,
	CTFGameRulesProxy = 170,
	CTFBaseProjectile = 158,
	CCaptureFlagReturnIcon = 22,
	CCaptureFlag = 21,
	CTETFParticleEffect = 153,
	CTETFExplosion = 152,
	CTETFBlood = 151,
	CTFWeaponSapper = 225,
	CTFWeaponBuilder = 217,
	CTeamTrainWatcher = 104,
	CTFTeam = 210,
	CTFTauntProp = 209,
	CTFProjectile_Rocket = 193,
	CTFProjectile_Arrow = 189,
	CTFPlayerResource = 188,
	CTFPlayer = 187,
	CTFRagdoll = 195,
	CTEPlayerAnimEvent = 139,
	CTFObjectiveResource = 183,
	CTFGlow = 171,
	CTFAmmoPack = 156,
	CObjectTeleporter = 71,
	CObjectSentrygun = 70,
	CTFProjectile_SentryRocket = 194,
	CObjectSapper = 69,
	CObjectCartDispenser = 67,
	CObjectDispenser = 68,
	CFuncRespawnRoomVisualizer = 56,
	CFuncRespawnRoom = 55,
	CFuncForceField = 50,
	CCaptureZone = 23,
	CBaseObject = 9,
	CTestTraceline = 150,
	CTEWorldDecal = 154,
	CTESpriteSpray = 148,
	CTESprite = 147,
	CTESparks = 146,
	CTESmoke = 145,
	CTEShowLine = 143,
	CTEProjectedDecal = 141,
	CTEPlayerDecal = 140,
	CTEPhysicsProp = 138,
	CTEParticleSystem = 137,
	CTEMuzzleFlash = 136,
	CTELargeFunnel = 134,
	CTEKillPlayerAttachments = 133,
	CTEImpact = 132,
	CTEGlowSprite = 131,
	CTEShatterSurface = 142,
	CTEFootprintDecal = 129,
	CTEFizz = 128,
	CTEExplosion = 127,
	CTEEnergySplash = 126,
	CTEEffectDispatch = 125,
	CTEDynamicLight = 124,
	CTEDecal = 122,
	CTEClientProjectile = 121,
	CTEBubbleTrail = 120,
	CTEBubbles = 119,
	CTEBSPDecal = 118,
	CTEBreakModel = 117,
	CTEBloodStream = 116,
	CTEBloodSprite = 115,
	CTEBeamSpline = 114,
	CTEBeamRingPoint = 113,
	CTEBeamRing = 112,
	CTEBeamPoints = 111,
	CTEBeamLaser = 110,
	CTEBeamFollow = 109,
	CTEBeamEnts = 108,
	CTEBeamEntPoint = 107,
	CTEBaseBeam = 106,
	CTEArmorRicochet = 105,
	CTEMetalSparks = 135,
	CSteamJet = 100,
	CSmokeStack = 94,
	DustTrail = 234,
	CFireTrail = 43,
	SporeTrail = 240,
	SporeExplosion = 239,
	RocketTrail = 237,
	SmokeTrail = 238,
	CPropVehicleDriveable = 86,
	ParticleSmokeGrenade = 236,
	CParticleFire = 72,
	MovieExplosion = 235,
	CTEGaussExplosion = 130,
	CEnvQuadraticBeam = 37,
	CEmbers = 30,
	CEnvWind = 41,
	CPrecipitation = 85,
	CBaseTempEntity = 15,
	CEconWearable = 29,
	CEconEntity = 28,
	CHandleTest = 61,
	CSpriteTrail = 99,
	CSpriteOriented = 98,
	CSprite = 97,
	CRagdollPropAttached = 89,
	CRagdollProp = 88,
	CPoseController = 84,
	CGameRulesProxy = 60,
	CInfoLadderDismount = 62,
	CFuncLadder = 51,
	CEnvDetailController = 34,
	CWorld = 233,
	CWaterLODControl = 231,
	CWaterBullet = 230,
	CVoteController = 229,
	CVGuiScreen = 228,
	CPropJeep = 0,
	CPropVehicleChoreoGeneric = 0,
	CTest_ProxyToggle_Networkable = 149,
	CTesla = 144,
	CTeam = 102,
	CSun = 101,
	CParticlePerformanceMonitor = 73,
	CSpotlightEnd = 96,
	CSlideshowDisplay = 93,
	CShadowControl = 92,
	CSceneEntity = 91,
	CRopeKeyframe = 90,
	CRagdollManager = 87,
	CPhysicsPropMultiplayer = 78,
	CPhysBoxMultiplayer = 76,
	CBasePropDoor = 14,
	CDynamicProp = 27,
	CPointCommentaryNode = 83,
	CPointCamera = 82,
	CPlayerResource = 81,
	CPlasma = 80,
	CPhysMagnet = 79,
	CPhysicsProp = 77,
	CPhysBox = 75,
	CParticleSystem = 74,
	CMaterialModifyControl = 66,
	CLightGlow = 65,
	CInfoOverlayAccessor = 64,
	CFuncTrackTrain = 59,
	CFuncSmokeVolume = 58,
	CFuncRotating = 57,
	CFuncReflectiveGlass = 54,
	CFuncOccluder = 53,
	CFuncMonitor = 52,
	CFunc_LOD = 47,
	CTEDust = 123,
	CFunc_Dust = 46,
	CFuncConveyor = 49,
	CBreakableSurface = 20,
	CFuncAreaPortalWindow = 48,
	CFish = 44,
	CEntityFlame = 32,
	CFireSmoke = 42,
	CEnvTonemapController = 40,
	CEnvScreenEffect = 38,
	CEnvScreenOverlay = 39,
	CEnvProjectedTexture = 36,
	CEnvParticleScript = 35,
	CFogController = 45,
	CEntityParticleTrail = 33,
	CEntityDissolve = 31,
	CDynamicLight = 26,
	CColorCorrectionVolume = 25,
	CColorCorrection = 24,
	CBreakableProp = 19,
	CBasePlayer = 12,
	CBaseFlex = 7,
	CBaseEntity = 6,
	CBaseDoor = 5,
	CBaseCombatCharacter = 3,
	CBaseAnimatingOverlay = 2,
	CBoneFollower = 18,
	CBaseAnimating = 1,
	CInfoLightingRelative = 63,
	CAI_BaseNPC = 0,
	CBeam = 17,
	CBaseViewModel = 16,
	CBaseProjectile = 13,
	CBaseParticleEntity = 11,
	CBaseGrenade = 8,
	CBaseCombatWeapon = 4
};