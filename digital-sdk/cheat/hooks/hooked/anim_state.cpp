#include "../hooks.h"

// @note: fixing weird landing animation
// @xref: https://www.unknowncheats.me/forum/counterstrike-global-offensive/504841-fixing-weird-landing-animation.html
void __fastcall hooks::hk_modify_eye_position( c_anim_state* anim_state, void* edx, c_vec3& input_eye_pos ) {
	if ( !anim_state )
		return og::m_modify_eye_position( anim_state, edx, input_eye_pos );

	if ( !anim_state->m_hit_ground && anim_state->m_duck_amount == 0.0f ) {
		anim_state->m_smooth_height_valid = false;
		anim_state->m_camera_smooth_height = 0x7F7FFFFF;
		return;
	}

	const auto head_bone = anim_state->m_player->lookup_bone( _( "head_0" ) );
	if ( head_bone == -1 )
		return;

	auto head_pos = anim_state->m_player->get_hitbox_pos( head_bone );
	head_pos.z += 1.7f;

	if ( input_eye_pos.z <= head_pos.z )
		return;

	const auto lol = abs( input_eye_pos.z - head_pos.z );
	float value = (lol - 4.0) * 0.16666667;
	value = std::clamp( value, 0.0f, 1.0f );

	const auto value_squared = value * value;
	input_eye_pos.z = (head_pos.z - input_eye_pos.z) * (value_squared * 3.0 - value_squared * 2.0 * value) + input_eye_pos.z;
}
