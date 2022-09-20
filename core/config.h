// -------------------------------------------------------------
//  Cubzh Core
//  config.h
//  Created by Adrien Duermael on July 20, 2015.
// -------------------------------------------------------------

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <assert.h>
#include <stdint.h>

#define vx_assert(_CONDITION) assert(_CONDITION)

#ifdef __VX_PLATFORM_WINDOWS
#define vx_deprecated(_MSG)
#else
#define vx_deprecated(_MSG) __attribute__((deprecated(_MSG)))
#endif

// GENERAL

#define MAP_DEFAULT_SCALE 5.0f
#define DEFAULT_USERNAME "noob" // used for display when player has no username

// FRAMES

#define MAX_TICK_DELTA_MS 50.0
#define TICK_DELTA_MS_T double
#define TICK_DELTA_SEC_T double

// PLAYER

#define PLAYER_ID_SERVER 255       // ID to represent the server
#define PLAYER_ID_ALL 254          // ID to represent all players
#define PLAYER_ID_ALL_BUT_SELF 253 // ID to represent all players except the local one
#define PLAYER_ID_LOCAL_TMP                                                                        \
    252                    // ID to represent local player on client side before ID is attributed
#define PLAYER_ID_NONE 251 // ID to represent no one

#define PLAYER_SCALE 0.5f

// walk animation ramps up from 0 to maximum motion force
#define PLAYER_WALK_MAX_SPEED 1.8f
#define PLAYER_WALK_MAX_MOTION_MAG 2500.0f
#define PLAYER_WAVE_SPEED 4.5f
#define PLAYER_TALK_SPEED 7.0f
#define PLAYER_SWING_SPEED 4.0f
#define PLAYER_BEAM_DURATION .6f
#define PLAYER_IDLE_SPEED 0.5f
#define PLAYER_ANIM_SPEED_WALK_RIGHT_ITEM 0.5f
#define PLAYER_ANIM_SPEED_HOLD_DRINK 0.5f
#define PLAYER_ANIM_SPEED_DRINK 2.0f

// EVENTS
#define EVENT_TYPE_FROM_SCRIPT 1
#define EVENT_TYPE_SERVER_LOG_INFO 2
#define EVENT_TYPE_SERVER_LOG_WARNING 3
#define EVENT_TYPE_SERVER_LOG_ERROR 4
#define EVENT_TYPE_FROM_SCRIPT_WITH_DEBUG                                                          \
    5 // sent as EVENT_TYPE_FROM_SCRIPT, with attached debug metadata

// UNDO MAXIMUM ACTIONS
#define NB_UNDOABLE_ACTIONS 20

// MARK: - Maths -

#define PI_F 3.14159265f
#define PI2_F 6.28318530f
#define PI_2_F (PI_F / 2.0f)
#define PI 3.14159265
#define DEGREES_TO_RADIANS (PI / 180.0)
#define DEGREES_TO_RADIANS_F (PI_F / 180.0f)
// 0: XYZ, 1: ZYX
#define ROTATION_ORDER 0

#define maximum(x, y) (((x) >= (y)) ? (x) : (y))
#define minimum(x, y) (((x) <= (y)) ? (x) : (y))
#define CLAMP(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))
#define CLAMP01(x) CLAMP(x, 0.0f, 1.0f)
#define LERP(a, b, v) ((a) + ((b) - (a)) * (v))

extern unsigned long upper_power_of_two(unsigned long v);

// MARK: - Epsilons -

/// Choosing an epsilon depends mostly on the meaning/unit of the value
/// W/o particular requirements, use the default EPSILON_ZERO, as using high epsilons can introduce
/// visible steps or flickering
#define EPSILON_0_0001_F 0.0001f

// epsilon for quaternion functions output, determined by the minimum error allowing
// quaternion_run_unit_tests() to pass
#define EPSILON_QUATERNION_ERROR 1e-6f

// generic epsilon-zero, eg. distances, scales, translations & forces (non-angular)
#define EPSILON_ZERO 1e-5f

// angular epsilon-zero for radian values
#define EPSILON_ZERO_RAD 1e-3f

#define EPSILON_COLLISION 1e-3f

// MARK: - PHYSICS -

/// Referred to as 'm', this is the min node capacity under which a node has to be removed
#define RTREE_NODE_MIN_CAPACITY 2
/// Referred to as 'M', this is the max node capacity over which a node has to be split
/// Note: M >= 2m to allow for split to not create any under-capacity nodes
#define RTREE_NODE_MAX_CAPACITY 4
/// Queries over large distances may be split in steps
#define RTREE_CAST_STEP_DISTANCE                                                                   \
    64.0f // 1/4 of a large-sized map, or "10 frames" of max velocity (PHYSICS_MAX_VELOCITY * .16)
/// Maximum velocity magnitude in unit/sec for all objects
#define PHYSICS_MAX_VELOCITY 400.0f
#define PHYSICS_MAX_SQR_VELOCITY 160000.0f
/// Threshold in world units under which bounce is muffled
#define PHYSICS_BOUNCE_THRESHOLD .7f
/// Multiple collision responses may fall within the same simulation frame, up to max iterations
#define PHYSICS_MAX_SOLVER_ITERATIONS 4
/// How to combine friction/bounciness of 2 rigidbodies in contact, min (0), max (1), or average (2)
#define PHYSICS_COMBINE_FRICTION_FUNC 2
#define PHYSICS_COMBINE_BOUNCINESS_FUNC 1
/// How to determine which face of a block was hit,
/// (0) per-face proximity,
///     - heavily reliant on the order of checks in case of ties, ie. the wrong face can be returned
///     - many cases can return FACE_NONE if outside the epsilon range
///     - cheap, only uses float_isEqual
/// (1) frustum checks from center of cube,
///     - works for any points since the entire space is divided into frustums from center of cube
///     - cannot return FACE_NONE
///     - slightly more expensive, uses up to 4 dot products
/// (2) improved (1) which first check in which corner the point is, then check only 2 planes
///     - same as (1) but uses 2 dot products
#define PHYSICS_IMPACT_FACE_MODE 2
/// Replacement happens backwards along the trajectory of a moving rigidbody (false),
/// or in any direction solely based on whether or not the boxes are already colliding (true)
/// Note: extra replacements only used against the map
#define PHYSICS_EXTRA_REPLACEMENTS false
/// Box sweep is checked in order of X, Y, Z and stops on first-in-order collision (false),
/// or checks every axes and ensures to return the minimum collision (true)
#define PHYSICS_FULL_BOX_SWEPT false
/// Threshold under which we consider there is no motion (ratio 0-1)
#define PHYSICS_STOP_MOTION_THRESHOLD .001f // 0.1% of motion left
/// Time (in frames) after which it's allowed to forget about a waiting end-of-contact callback
#define PHYSICS_DISCARD_COLLISION_COUPLE 36000
/// Number of frames during which an awaken rigidbody will skip sleep conditions, max 255 (uint8)
#define PHYSICS_AWAKE_FRAMES 6
#define PHYSICS_AWAKE_DISTANCE EPSILON_COLLISION * 2

/// Physics collision masks default values
#define PHYSICS_GROUP_NONE 0
#define PHYSICS_GROUP_ALL 255
#define PHYSICS_GROUP_DEFAULT_MAP 1
#define PHYSICS_COLLIDESWITH_DEFAULT_MAP PHYSICS_GROUP_NONE
#define PHYSICS_GROUP_DEFAULT_PLAYER 2
#define PHYSICS_COLLIDESWITH_DEFAULT_PLAYER 1 // map
#define PHYSICS_GROUP_DEFAULT_OBJECT 4
#define PHYSICS_COLLIDESWITH_DEFAULT_OBJECT 5 // map + object

/// Permanent absorption of any force in given environment, currently we only have air drag
/// This could become configurable in Lua, and could be a property of pass-through rigidbodies
#define PHYSICS_AIR_DRAG_DEFAULT 0.001f
#define PHYSICS_GRAVITY -225.0f // strong gravity makes movement more dynamic

/// Physics properties default values
#define PHYSICS_MASS_DEFAULT 1.0f
#define PHYSICS_FRICTION_DEFAULT .2f
#define PHYSICS_BOUNCINESS_DEFAULT .3f
#define PHYSICS_MASS_PLAYER 1.0f
#define PHYSICS_FRICTION_PLAYER .95f
#define PHYSICS_BOUNCINESS_PLAYER 0.0f
#define PHYSICS_MASS_MAP 1e9f
#define PHYSICS_FRICTION_MAP .95f
#define PHYSICS_BOUNCINESS_MAP 0.0f

// MARK: - PALETTES -

// No default palette used
#define PALETTE_ID_CUSTOM 0
// Legacy default palette, from iOS item editor (app released in 2017), 112 colors, pico8+
#define PALETTE_ID_IOS_ITEM_EDITOR_LEGACY 1
// Current default palette, from 2021, 252 colors, includes semi-transparent colors
#define PALETTE_ID_2021 2

// MARK: - SHAPES -

// coords of block within shape
typedef int16_t SHAPE_COORDS_INT_T;
typedef uint16_t SHAPE_SIZE_INT_T;
// coords of block within chunk
typedef int8_t CHUNK_COORDS_INT_T;

typedef uint8_t SHAPE_COLOR_INDEX_INT_T;
typedef uint32_t ATLAS_COLOR_INDEX_INT_T;

// color index for air block inside shape octree
#define SHAPE_COLOR_INDEX_AIR_BLOCK 255
#define SHAPE_COLOR_INDEX_MAX_COUNT 128

// Dimensions of the atlas renderer-side: COLOR_ATLAS_SIZE * COLOR_ATLAS_SIZE, original +
// complementary colors Dimensions of the data C-side: COLOR_ATLAS_SIZE * COLOR_ATLAS_SIZE / 2,
// unique colors
#define COLOR_ATLAS_SIZE 512
#define ATLAS_COLOR_INDEX_MAX_COUNT 131072
#define ATLAS_COLOR_INDEX_ERROR 999999

typedef uint8_t FACE_INDEX_INT_T;

typedef struct {
    uint8_t ambient : 4;
    uint8_t red : 4;
    uint8_t green : 4;
    uint8_t blue : 4;
} VERTEX_LIGHT_STRUCT_T;
#define DEFAULT_LIGHT(l)                                                                           \
    l.ambient = 15;                                                                                \
    l.red = l.green = l.blue = 0;
#define ZERO_LIGHT(l) l.ambient = l.red = l.green = l.blue = 0;

// one uint8_t is enough to store ambient occlusion value for each one
// of the 4 corners. (4 possible values for each)
typedef struct {
    uint8_t ao1 : 2;
    uint8_t ao2 : 2;
    uint8_t ao3 : 2;
    uint8_t ao4 : 2;
} FACE_AMBIENT_OCCLUSION_STRUCT_T;

// FACES

static const FACE_INDEX_INT_T FACE_RIGHT = 0;
static const FACE_INDEX_INT_T FACE_LEFT = 1;
static const FACE_INDEX_INT_T FACE_FRONT = 2;
static const FACE_INDEX_INT_T FACE_BACK = 3;
static const FACE_INDEX_INT_T FACE_TOP = 4;
static const FACE_INDEX_INT_T FACE_DOWN = 5;
static const FACE_INDEX_INT_T FACE_SIZE = 6;
static const FACE_INDEX_INT_T FACE_NONE = 7;

// switch cases can only use compile time constants.
// Redefining face indexes here for that purpose
#define FACE_RIGHT_CTC 0
#define FACE_LEFT_CTC 1
#define FACE_FRONT_CTC 2
#define FACE_BACK_CTC 3
#define FACE_TOP_CTC 4
#define FACE_DOWN_CTC 5
#define FACE_SIZE_CTC 6
#define FACE_NONE_CTC 7

// CHUNKS
// In Minecraft, a chunk is a column. (i.e. 16x16x128)
// It may be better to use cubes and don't limit
// world height depending on chunk height. It should
// be an othet variable, and we should be able to display
// fog vertically as well (depending on view distance)
#define CHUNK_HEIGHT 16
#define CHUNK_WIDTH 16
#define CHUNK_DEPTH 16
// used to divide
#define CHUNK_HEIGHT_SQRT 4
#define CHUNK_WIDTH_SQRT 4
#define CHUNK_DEPTH_SQRT 4
// used to get modulo
#define CHUNK_HEIGHT_MINUS_ONE 15
#define CHUNK_WIDTH_MINUS_ONE 15
#define CHUNK_DEPTH_MINUS_ONE 15

// VERTEX BUFFERS
// Note (disambiguation): Cubzh Core's "VB" hold face data and is NOT equivalent to the "VB" that
// drives drawcalls Maximum allowed capacity for a single vertex buffer, this should be matched by
// renderer max texture size
#define VERTEX_BUFFER_MAX_COUNT 1048576
#define VERTEX_BUFFER_MIN_COUNT 4096
// Minimal size for the first VB at runtime, see shape_add_vertex_buffer
#define VERTEX_BUFFER_RUNTIME_COUNT 4096
// Estimated shape volume block-occupancy
#define VERTEX_BUFFER_VOLUME_OCCUPANCY 0.08f
// Final VB capacity multiplier if shape volume was predominant, can be thought of as block-to-faces
// factor for shape volume
#define VERTEX_BUFFER_VOLUME_FACTOR 3
// Final VB capacity multiplier if shape shell was predominant, can be thought of as block-to-faces
// factor for shape shell
#define VERTEX_BUFFER_SHELL_FACTOR 2.0f
// Additional factor for transparent VB capacity
#define VERTEX_BUFFER_TRANSPARENT_FACTOR 0.25f
// Subsequent VBs on init/runtime can be downscaled or upscaled, see shape_add_vertex_buffer
#define VERTEX_BUFFER_INIT_SCALE_RATE .75f
#define VERTEX_BUFFER_RUNTIME_SCALE_RATE 4.0f
// Ensure VB size will result in POT texture size (required for compressed texture formats)
// Note: if POT expected, downscale should be 0.25f and upscale 4.0f or upper POT is used
#define VERTEX_BUFFER_TEX_UPPER_POT false

//// Disabling global lighting will use neutral value (15, 0, 0, 0) everywhere
#define GLOBAL_LIGHTING_ENABLED true
#define GLOBAL_LIGHTING_SMOOTHING_ENABLED true
#define GLOBAL_LIGHTING_BAKE_READ_ENABLED true
#define GLOBAL_LIGHTING_BAKE_WRITE_ENABLED true
/// Save file in cache if baked lighting wasn't present for a game map,
/// new file path prefixed with "baked_" and suffixed with game ID
#define GLOBAL_LIGHTING_BAKE_SAVE_ENABLED true
/// Checks if a "baked_" file exists first when loading a game map
#define GLOBAL_LIGHTING_BAKE_LOAD_ENABLED true

//// Function used for vertex light smoothing
/// Note: this affects only light intensity value, rgb values are always averaged
/// 0 : average
/// 1 : minimum
/// 2 : maximum
#define VERTEX_LIGHT_SMOOTHING 1

/// AO light coef multiplies the gradient values when pre-applied to sunlight color
/// in the lighting texture ie. only shapes w/ lighting benefits from this coef ; dynamic shapes
/// using approximate lighting use the coef defined shader-side in voxels_config.sh
#define AO_LIGHT_COEF 0.24f
//// AO gradient values
static float AO_GRADIENT_BASE_F[4] = {0.0f, 0.6f, 0.8f, 1.0f};

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wold-style-cast"
static uint8_t AO_GRADIENT[4] = {0,
                                 (uint8_t)(15.0f * 0.6f * AO_LIGHT_COEF),
                                 (uint8_t)(15.0f * 0.8f * AO_LIGHT_COEF),
                                 (uint8_t)(15.0f * 1.0f * AO_LIGHT_COEF)};
#pragma clang diagnostic pop

//// AO hue step settings, these are a copy of the settings in voxels_config.sh for offline
/// calculation
#define AO_COLOR_HUE_STEP 0.25f * PI_F
#define AO_COLOR_HUE_THRESHOLD_DIR -.75f * PI_F   // green
#define AO_COLOR_HUE_THRESHOLD_TARGET .75f * PI_F // blue
#define AO_COLOR_HUE_CLAMP_TARGET true

//// Triangle shift is used to make sure the diagonal is 'cutting' the gradient to avoid
/// creating a shadow "square", it can use
/// 0 : AO only, this creates favourable diagonals for the AO value only
/// 1 : final ambient light value, this shifts triangles based on the highest contrast diagonal
/// 2 : mixed, uses (1) if diagonals diff is higher than TRIANGLE_SHIFT_MIXED_THRESHOLD, else (0)
/// 3 : mixed w/ emission, based on both sunlight value delta and luminance from RGB delta
#define TRIANGLE_SHIFT_MODE 3
#define TRIANGLE_SHIFT_MIXED_THRESHOLD 3
#define TRIANGLE_SHIFT_MIXED_THRESHOLD_LUMA 0.1f

#define SUNLIGHT_PROPAGATION_STEP 1 // note: top-down step is always 0
#define EMISSION_PROPAGATION_STEP 1

#define ENABLE_TRANSPARENCY true
/// Whether transparent blocks should be AO casters and/or AO receivers, or none
#define ENABLE_TRANSPARENCY_AO_CASTER false
#define ENABLE_TRANSPARENCY_AO_RECEIVER true
//// When light propagates in a transparent block, a fraction of its values can be absorbed
/// based on opacity value, it can use different easing
/// 0 : linear
/// 1 : quadratic ease-in
/// 2 : cubic ease-in
/// 3 : exponential ease-in
/// 4 : circular ease-in
#define TRANSPARENCY_ABSORPTION_FUNC 4
/// true : reduce by max(absorption, step)
/// false : reduce by absorption, then apply step
#define TRANSPARENCY_ABSORPTION_MAX_STEP true
/// Whether transparent inner faces between 2 blocks of a different color should be drawn
#define ENABLE_TRANSPARENCY_INNER_FACES true

// MARK: - Touch events -

#define TOUCH_EVENT_FINGER_1 0 // touch ID for 1st finger
#define TOUCH_EVENT_FINGER_2 1 // touch ID for 2nd finger
#define TOUCH_EVENT_MAXCOUNT 2 // touch IDs are 0 to TOUCH_EVENT_MAXCOUNT excluded
#define INDEX_MOUSE_LEFTBUTTON TOUCH_EVENT_MAXCOUNT
#define INDEX_MOUSE_RIGHTBUTTON (INDEX_MOUSE_LEFTBUTTON + 1)
#define TOUCH_AND_MOUSE_EVENT_MAXINDEXCOUNT (INDEX_MOUSE_RIGHTBUTTON + 1)

// --------------------------------------------------
// MARK: - Game launch options -
// --------------------------------------------------

// #define DEV_MODE true
#define GAME_LAUNCH_DEV_MODE true
#define GAME_LAUNCH_NOT_DEV_MODE false

// #define LOCAL_SERVER true
#define GAME_LAUNCH_DISTANT_SERVER false

//
// MARK: - SIGN IN -
//

#define SIGNIN_DEFAULT_INPUT_MAX_CHARS 512

#ifdef __cplusplus
} // extern "C"
#endif