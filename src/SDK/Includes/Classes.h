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
	TF_WEAPON_NONE = 0,
	TF_WEAPON_BAT,
	TF_WEAPON_BOTTLE,
	TF_WEAPON_FIREAXE,
	TF_WEAPON_CLUB,
	TF_WEAPON_CROWBAR,
	TF_WEAPON_KNIFE,
	TF_WEAPON_FISTS,
	TF_WEAPON_SHOVEL,
	TF_WEAPON_WRENCH,
	TF_WEAPON_BONESAW,
	TF_WEAPON_SHOTGUN_PRIMARY,
	TF_WEAPON_SHOTGUN_SOLDIER,
	TF_WEAPON_SHOTGUN_HWG,
	TF_WEAPON_SHOTGUN_PYRO,
	TF_WEAPON_SCATTERGUN,
	TF_WEAPON_SNIPERRIFLE,
	TF_WEAPON_MINIGUN,
	TF_WEAPON_SMG,
	TF_WEAPON_SYRINGEGUN_MEDIC,
	TF_WEAPON_TRANQ,
	TF_WEAPON_ROCKETLAUNCHER,
	TF_WEAPON_GRENADELAUNCHER,
	TF_WEAPON_PIPEBOMBLAUNCHER,
	TF_WEAPON_FLAMETHROWER,
	TF_WEAPON_GRENADE_NORMAL,
	TF_WEAPON_GRENADE_CONCUSSION,
	TF_WEAPON_GRENADE_NAIL,
	TF_WEAPON_GRENADE_MIRV,
	TF_WEAPON_GRENADE_MIRV_DEMOMAN,
	TF_WEAPON_GRENADE_NAPALM,
	TF_WEAPON_GRENADE_GAS,
	TF_WEAPON_GRENADE_EMP,
	TF_WEAPON_GRENADE_CALTROP,
	TF_WEAPON_GRENADE_PIPEBOMB,
	TF_WEAPON_GRENADE_SMOKE_BOMB,
	TF_WEAPON_GRENADE_HEAL,
	TF_WEAPON_PISTOL,
	TF_WEAPON_PISTOL_SCOUT,
	TF_WEAPON_REVOLVER,
	TF_WEAPON_NAILGUN,
	TF_WEAPON_PDA,
	TF_WEAPON_PDA_ENGINEER_BUILD,
	TF_WEAPON_PDA_ENGINEER_DESTROY,
	TF_WEAPON_PDA_SPY,
	TF_WEAPON_BUILDER,
	TF_WEAPON_MEDIGUN,
	TF_WEAPON_GRENADE_MIRVBOMB,
	TF_WEAPON_FLAMETHROWER_ROCKET,
	TF_WEAPON_GRENADE_DEMOMAN,
	TF_WEAPON_SENTRY_BULLET,
	TF_WEAPON_SENTRY_ROCKET,
	TF_WEAPON_DISPENSER,
	TF_WEAPON_INVIS,
	TF_WEAPON_FLAG,
	TF_WEAPON_FLAREGUN,
	TF_WEAPON_LUNCHBOX,
	TF_WEAPON_COMPOUND_BOW,
	// ADD TF2C WEAPONS AFTER THIS
	TF_WEAPON_HUNTERRIFLE,
	TF_WEAPON_UMBRELLA,
	TF_WEAPON_HAMMERFISTS,
	TF_WEAPON_CHAINSAW,
	TF_WEAPON_HEAVYARTILLERY,
	TF_WEAPON_ASSAULTRIFLE,
	TF_WEAPON_DISPLACER,

	TF_WEAPON_COUNT
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
	CTFUmbrella = 220,
	CTFTranq = 219,
	CTFWeaponThrowable = 235,
	CTFTaser = 216,
	CTFRussianRoulette = 206,
	CTFNailgun = 189,
	CTFWeaponMirv2 = 229,
	CTFWeaponMirv = 228,
	CTFHunterRifle = 184,
	CTFGrenadeMirvBomb = 180,
	CTFGrenadeMirvProjectile = 181,
	CTFDoubleShotgun = 172,
	CTFCoilGun = 170,
	CTFBeacon = 165,
	CTFAAGun = 159,
	CTFWeaponBaseMelee = 224,
	CTFWeaponBaseGun = 223,
	CTFWeaponBase = 222,
	CTFWrench = 237,
	CTFSyringeGun = 215,
	CSniperDot = 97,
	CTFSniperRifle = 214,
	CTFSMG = 213,
	CTFShovel = 212,
	CTFScatterGun = 207,
	CTFShotgun_Pyro = 210,
	CTFShotgun_HWG = 209,
	CTFShotgun_Soldier = 211,
	CTFShotgun = 208,
	CTFRocketLauncher = 205,
	CTFRevolver = 204,
	CTFPistol_Scout = 193,
	CTFPistol = 192,
	CTFPipebombLauncher = 191,
	CTFWeaponPDA_Spy = 233,
	CTFWeaponPDA_Engineer_Destroy = 232,
	CTFWeaponPDA_Engineer_Build = 231,
	CTFWeaponPDA = 230,
	CTFMinigun = 188,
	CWeaponMedigun = 242,
	CTFLunchBox = 187,
	CTFKnife = 186,
	CTFWeaponInvis = 227,
	CTFGrenadeLauncher = 179,
	CTFFlareGun = 176,
	CTFFlameThrower = 175,
	CTFFists = 174,
	CTFFireAxe = 173,
	CTFWeaponCubemap = 226,
	CTFCompoundBow = 171,
	CTFClub = 169,
	CTFBottle = 167,
	CTFBonesaw = 166,
	CTFBat = 164,
	CTFWearable = 236,
	CTFBaseRocket = 163,
	CTFBaseGrenade = 161,
	CTFGrenadeStickybombProjectile = 183,
	CTFGrenadePipebombProjectile = 182,
	CTFViewModel = 221,
	CTeamRoundTimer = 106,
	CTFRandomizerManagerProxy = 203,
	CTFProjectile_Flare = 199,
	CTFProjectile_Dart = 198,
	CTFProjectile_Coil = 197,
	CTFBrickProjectile = 168,
	CBaseObjectUpgrade = 10,
	CTFItem = 185,
	CTeamGenerator = 105,
	CTeamShield = 107,
	CTFGameRulesProxy = 177,
	CTFBaseProjectile = 162,
	CCaptureFlagReturnIcon = 22,
	CCaptureFlag = 21,
	CTETFParticleEffect = 157,
	CTETFExplosion = 156,
	CTETFBlood = 155,
	CTFWeaponSapper = 234,
	CTFWeaponBuilder = 225,
	CTeamTrainWatcher = 108,
	CTFTeam = 218,
	CTFTauntProp = 217,
	CTFProjectile_Rocket = 200,
	CTFProjectile_Arrow = 196,
	CTFPlayerResource = 195,
	CTFPlayer = 194,
	CTFRagdoll = 202,
	CTEPlayerAnimEvent = 143,
	CTFObjectiveResource = 190,
	CTFGlow = 178,
	CTFAmmoPack = 160,
	CObjectTeleporter = 73,
	CObjectSentrygun = 72,
	CTFProjectile_SentryRocket = 201,
	CObjectSapper = 71,
	CObjectJumppad = 70,
	CObjectCartDispenser = 68,
	CObjectDispenser = 69,
	CFuncRespawnRoomVisualizer = 57,
	CFuncRespawnRoom = 56,
	CFuncForceField = 51,
	CFuncFilterVisualizer = 50,
	CCaptureZone = 23,
	CBaseObject = 9,
	CTestTraceline = 154,
	CTEWorldDecal = 158,
	CTESpriteSpray = 152,
	CTESprite = 151,
	CTESparks = 150,
	CTESmoke = 149,
	CTEShowLine = 147,
	CTEProjectedDecal = 145,
	CTEPlayerDecal = 144,
	CTEPhysicsProp = 142,
	CTEParticleSystem = 141,
	CTEMuzzleFlash = 140,
	CTELargeFunnel = 138,
	CTEKillPlayerAttachments = 137,
	CTEImpact = 136,
	CTEGlowSprite = 135,
	CTEShatterSurface = 146,
	CTEFootprintDecal = 133,
	CTEFizz = 132,
	CTEExplosion = 131,
	CTEEnergySplash = 130,
	CTEEffectDispatch = 129,
	CTEDynamicLight = 128,
	CTEDecal = 126,
	CTEClientProjectile = 125,
	CTEBubbleTrail = 124,
	CTEBubbles = 123,
	CTEBSPDecal = 122,
	CTEBreakModel = 121,
	CTEBloodStream = 120,
	CTEBloodSprite = 119,
	CTEBeamSpline = 118,
	CTEBeamRingPoint = 117,
	CTEBeamRing = 116,
	CTEBeamPoints = 115,
	CTEBeamLaser = 114,
	CTEBeamFollow = 113,
	CTEBeamEnts = 112,
	CTEBeamEntPoint = 111,
	CTEBaseBeam = 110,
	CTEArmorRicochet = 109,
	CTEMetalSparks = 139,
	CSteamJet = 102,
	CSmokeStack = 96,
	DustTrail = 244,
	CFireTrail = 43,
	SporeTrail = 250,
	SporeExplosion = 249,
	RocketTrail = 247,
	SmokeTrail = 248,
	CPropVehicleDriveable = 88,
	ParticleSmokeGrenade = 246,
	CParticleFire = 74,
	MovieExplosion = 245,
	CTEGaussExplosion = 134,
	CEnvQuadraticBeam = 37,
	CEmbers = 30,
	CEnvWind = 41,
	CPrecipitation = 87,
	CBaseTempEntity = 15,
	CEconWearable = 29,
	CEconEntity = 28,
	CHandleTest = 62,
	CSpriteTrail = 101,
	CSpriteOriented = 100,
	CSprite = 99,
	CRagdollPropAttached = 91,
	CRagdollProp = 90,
	CPoseController = 86,
	CGameRulesProxy = 61,
	CInfoLadderDismount = 63,
	CFuncLadder = 52,
	CEnvDetailController = 34,
	CWorld = 243,
	CWaterLODControl = 241,
	CWaterBullet = 240,
	CVoteController = 239,
	CVGuiScreen = 238,
	CPropJeep = 0,
	CPropVehicleChoreoGeneric = 0,
	CTest_ProxyToggle_Networkable = 153,
	CTesla = 148,
	CTeam = 104,
	CSun = 103,
	CParticlePerformanceMonitor = 75,
	CSpotlightEnd = 98,
	CSlideshowDisplay = 95,
	CShadowControl = 94,
	CSceneEntity = 93,
	CRopeKeyframe = 92,
	CRagdollManager = 89,
	CPhysicsPropMultiplayer = 80,
	CPhysBoxMultiplayer = 78,
	CBasePropDoor = 14,
	CDynamicProp = 27,
	CPointCommentaryNode = 85,
	CPointCamera = 84,
	CPlayerResource = 83,
	CPlasma = 82,
	CPhysMagnet = 81,
	CPhysicsProp = 79,
	CPhysBox = 77,
	CParticleSystem = 76,
	CMaterialModifyControl = 67,
	CLightGlow = 66,
	CInfoOverlayAccessor = 65,
	CFuncTrackTrain = 60,
	CFuncSmokeVolume = 59,
	CFuncRotating = 58,
	CFuncReflectiveGlass = 55,
	CFuncOccluder = 54,
	CFuncMonitor = 53,
	CFunc_LOD = 47,
	CTEDust = 127,
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
	CInfoLightingRelative = 64,
	CAI_BaseNPC = 0,
	CBeam = 17,
	CBaseViewModel = 16,
	CBaseProjectile = 13,
	CBaseParticleEntity = 11,
	CBaseGrenade = 8,
	CBaseCombatWeapon = 4
};