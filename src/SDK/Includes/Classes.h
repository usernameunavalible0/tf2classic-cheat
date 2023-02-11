#pragma once
#include "vector.h"

enum StereoEye_t
{
	STEREO_EYE_MONO = 0,
	STEREO_EYE_LEFT = 1,
	STEREO_EYE_RIGHT = 2,
	STEREO_EYE_MAX = 3,
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