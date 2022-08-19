#pragma once
#include "../../includes.h"
#include "../../sdk/sdk.h"
#include "../features/features.h"
#include "../menu/menu.h"

#define HOOK(target, detour, og) \
	if (MH_CreateHook( target, detour, reinterpret_cast<void**>(&(og))) == MH_OK && MH_EnableHook( target ) == MH_OK ) {\
		printf("created target: 0x%p, detour: 0x%p, og: 0x%p\n", target, detour, og); hooks::m_targets.emplace_back(target);\
	}

using create_move_t = void( __stdcall* )(int, float, bool);
using lock_cursor_t = void( __thiscall* )(void*);

namespace hooks {
	void __stdcall hk_create_move( int sequence, float frame_time, bool is_active, bool& send_packet );
	void __stdcall hk_create_move_proxy( int sequence, float frame_time, bool is_active );
	void __fastcall hk_calculate_view( c_base_player* player, void* edx, c_vec3& eye_origin, qangle_t& eye_angles, float& z_near,
									   float& z_far, float& fov );
	void __fastcall hk_modify_eye_position( c_anim_state* anim_state, void* edx, c_vec3& input_eye_pos );
	void __fastcall hk_inferno_client_think( i_base_client_dll* client, void* edx );
	void _cdecl hk_blood_spray_callback( );
	void __fastcall hk_override_view( void* ecx, void* edx, c_view_setup* setup_view );
	void __fastcall hk_paint_traverse( i_panel* vpanel, void* edx, vgui::vpanel panel, bool force_repaint, bool allow_force );
	long __stdcall hk_reset( IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params );
	long __stdcall hk_present( IDirect3DDevice9* device, RECT* src, RECT* dest, HWND window_override, RGNDATA* dirty_region );
	void __fastcall hk_lock_cursor( i_surface* surface, void* edx );
	void __fastcall hk_do_extra_bone_processing( c_base_player* player, void* edx, int a2, int a3, int a4, int a5, int a6, int a7 );
	bool __fastcall hk_setup_bones( c_base_player* player, void* edx, matrix_t* matrix, int max_bones, int bone_mask, float current_time );
	bool __fastcall hk_should_skip_anim_frame( c_base_player* player, void* edx );
	void __fastcall hk_build_transformations( c_base_player* player, void* edx, void* a2, int a3, int a4, int a5, int a6, int a7 );
	void __fastcall hk_standard_blending_rules( c_base_player* player, void* edx, void* a2, int a3, void* a4, int a5, int a6 );
	bool __fastcall hk_is_paused( i_engine* engine, void* edx );
	bool __fastcall hk_is_hltv( i_engine* engine, void* edx );
	void __fastcall hk_draw_model_execute( i_model_render* model_render, void* edx, void* ctx, draw_model_state_t& state, model_render_info_t& info, matrix_t* custom_bone_to_world );
	float __fastcall hk_get_fov( c_base_player* player, void* edx );
	void __fastcall hk_get_color_modulation( i_material* material, void* edx, float* r, float* g, float* b );
	float __fastcall hk_get_alpha_modulation( i_material* material, void* edx );
	void init_wnd_proc( );
	long __stdcall hk_wnd_proc( HWND window, UINT msg, WPARAM wparm, LPARAM lparm );
	void unhook( LPVOID target );
	void disable_all_hooks( );
	void init( );

	namespace og {
		inline create_move_t m_create_move{};
		inline WNDPROC m_wnd_proc{};

		inline decltype(&hk_get_alpha_modulation) m_get_alpha_modulation{};
		inline decltype(&hk_get_color_modulation) m_get_color_modulation{};
		inline decltype(&hk_get_fov) m_get_fov{};
		inline decltype(&hk_draw_model_execute) m_draw_model_execute{};
		inline decltype(&hk_lock_cursor) m_lock_cursor{};
		inline decltype(&hk_build_transformations) m_build_transformations{};
		inline decltype(&hk_standard_blending_rules) m_standard_blending_rules{};
		inline decltype(&hk_present) m_present{};
		inline decltype(&hk_reset) m_reset{};
		inline decltype(&hk_paint_traverse) m_paint_traverse{};
		inline decltype(&hk_override_view) m_override_view{};
		inline decltype(&hk_modify_eye_position) m_modify_eye_position{};
		inline decltype(&hk_calculate_view) m_calculate_view{};
		inline decltype(&hk_blood_spray_callback) m_blood_spray_callback{};
		inline decltype(&hk_do_extra_bone_processing) m_do_extra_bone_processing;
		inline decltype(&hk_setup_bones) m_setup_bones;
		inline decltype(&hk_should_skip_anim_frame) m_should_skip_anim_frame;
		inline decltype(&hk_inferno_client_think) m_inferno_client_think{};
		inline decltype(&hk_is_paused) m_is_paused{};
		inline decltype(&hk_is_hltv) m_is_hltv{};
	}
	inline std::vector<LPVOID> m_targets{};
}