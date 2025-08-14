#include "graphics/font_0_large.xbm"
#include "graphics/font_1_large.xbm"
#include "graphics/font_2_large.xbm"
#include "graphics/font_3_large.xbm"
#include "graphics/font_4_large.xbm"
#include "graphics/font_5_large.xbm"
#include "graphics/font_6_large.xbm"
#include "graphics/font_7_large.xbm"
#include "graphics/font_8_large.xbm"
#include "graphics/font_9_large.xbm"
#include "graphics/font_a_large.xbm"
#include "graphics/font_b_large.xbm"
#include "graphics/font_capC_large.xbm"
#include "graphics/font_capH_large.xbm"
#include "graphics/font_capP_large.xbm"
#include "graphics/font_capR_large.xbm"
#include "graphics/font_colon_large.xbm"
#include "graphics/font_c_large.xbm"
#include "graphics/font_degree_large.xbm"
#include "graphics/font_dot_large.xbm"
#include "graphics/font_d_large.xbm"
#include "graphics/font_e_large.xbm"
#include "graphics/font_f_large.xbm"
#include "graphics/font_g_large.xbm"
#include "graphics/font_i_large.xbm"
#include "graphics/font_j_large.xbm"
#include "graphics/font_k_large.xbm"
#include "graphics/font_l_large.xbm"
#include "graphics/font_m_large.xbm"
#include "graphics/font_n_large.xbm"
#include "graphics/font_o_large.xbm"
#include "graphics/font_percent_large.xbm"
#include "graphics/font_p_large.xbm"
#include "graphics/font_r_large.xbm"
#include "graphics/font_s_large.xbm"
#include "graphics/font_t_large.xbm"
#include "graphics/font_u_large.xbm"
#include "graphics/font_v_large.xbm"
#include "graphics/font_w_large.xbm"
#include "graphics/font_z_large.xbm"
#include "graphics/font_0_small.xbm"
#include "graphics/font_1_small.xbm"
#include "graphics/font_2_small.xbm"
#include "graphics/font_3_small.xbm"
#include "graphics/font_4_small.xbm"
#include "graphics/font_5_small.xbm"
#include "graphics/font_6_small.xbm"
#include "graphics/font_7_small.xbm"
#include "graphics/font_8_small.xbm"
#include "graphics/font_9_small.xbm"
#include "graphics/font_b_small.xbm"
#include "graphics/font_capC_small.xbm"
#include "graphics/font_dash_small.xbm"
#include "graphics/font_degree_small.xbm"
#include "graphics/font_f_small.xbm"
#include "graphics/font_m_small.xbm"
#include "graphics/font_t_small.xbm"
#include "graphics/arrow_n.xbm"
#include "graphics/arrow_no.xbm"
#include "graphics/arrow_nw.xbm"
#include "graphics/arrow_o.xbm"
#include "graphics/arrow_w.xbm"
#include "graphics/arrow_z.xbm"
#include "graphics/arrow_zo.xbm"
#include "graphics/arrow_zw.xbm"
#include "graphics/icon_co2.xbm"
#include "graphics/icon_humid.xbm"
#include "graphics/icon_pres.xbm"
#include "graphics/icon_temp.xbm"
#include "graphics/weather_clouded.xbm"
#include "graphics/weather_fog.xbm"
#include "graphics/weather_lightning.xbm"
#include "graphics/weather_night.xbm"
#include "graphics/weather_nightclouded.xbm"
#include "graphics/weather_nightfog.xbm"
#include "graphics/weather_nightlightning.xbm"
#include "graphics/weather_nightrain.xbm"
#include "graphics/weather_nightsnow.xbm"
#include "graphics/weather_rain.xbm"
#include "graphics/weather_snow.xbm"
#include "graphics/weather_sunny.xbm"
#include "graphics/weather_sunnyclouded.xbm"
#include "graphics/weather_sunnyfog.xbm"
#include "graphics/weather_sunnylightning.xbm"
#include "graphics/weather_sunnyrain.xbm"
#include "graphics/weather_sunnysnow.xbm"
#include "graphics/weather_unknown.xbm"

#define FONT_LARGE_BASELINE 5
#define FONT_LARGE_PADDING 3
#define FONT_SMALL_PADDING 2


struct Bitmap
{
    unsigned char* name;
    unsigned char* bits;
    int width;
    int height;
};

const Bitmap font_large[40] = 
{
    { '0', font_0_large_bits, font_0_large_width, font_0_large_height },
    { '1', font_1_large_bits, font_1_large_width, font_1_large_height },
    { '2', font_2_large_bits, font_2_large_width, font_2_large_height },
    { '3', font_3_large_bits, font_3_large_width, font_3_large_height },
    { '4', font_4_large_bits, font_4_large_width, font_4_large_height },
    { '5', font_5_large_bits, font_5_large_width, font_5_large_height },
    { '6', font_6_large_bits, font_6_large_width, font_6_large_height },
    { '7', font_7_large_bits, font_7_large_width, font_7_large_height },
    { '8', font_8_large_bits, font_8_large_width, font_8_large_height },
    { '9', font_9_large_bits, font_9_large_width, font_9_large_height },
    { 'a', font_a_large_bits, font_a_large_width, font_a_large_height },
    { 'b', font_b_large_bits, font_b_large_width, font_b_large_height },
    { 'C', font_C_large_bits, font_C_large_width, font_C_large_height },
    { 'H', font_H_large_bits, font_H_large_width, font_H_large_height },
    { 'P', font_P_large_bits, font_P_large_width, font_P_large_height },
    { 'R', font_R_large_bits, font_R_large_width, font_R_large_height },
    { ':', font_colon_large_bits, font_colon_large_width, font_colon_large_height },
    { 'c', font_c_large_bits, font_c_large_width, font_c_large_height },
    { '°', font_degree_large_bits, font_degree_large_width, font_degree_large_height },
    { '.', font_dot_large_bits, font_dot_large_width, font_dot_large_height },
    { 'd', font_d_large_bits, font_d_large_width, font_d_large_height },
    { 'e', font_e_large_bits, font_e_large_width, font_e_large_height },
    { 'f', font_f_large_bits, font_f_large_width, font_f_large_height },
    { 'g', font_g_large_bits, font_g_large_width, font_g_large_height },
    { 'i', font_i_large_bits, font_i_large_width, font_i_large_height },
    { 'j', font_j_large_bits, font_j_large_width, font_j_large_height },
    { 'k', font_k_large_bits, font_k_large_width, font_k_large_height },
    { 'l', font_l_large_bits, font_l_large_width, font_l_large_height },
    { 'm', font_m_large_bits, font_m_large_width, font_m_large_height },
    { 'n', font_n_large_bits, font_n_large_width, font_n_large_height },
    { 'o', font_o_large_bits, font_o_large_width, font_o_large_height },
    { '%', font_percent_large_bits, font_percent_large_width, font_percent_large_height },
    { 'p', font_p_large_bits, font_p_large_width, font_p_large_height },
    { 'r', font_r_large_bits, font_r_large_width, font_r_large_height },
    { 's', font_s_large_bits, font_s_large_width, font_s_large_height },
    { 't', font_t_large_bits, font_t_large_width, font_t_large_height },
    { 'u', font_u_large_bits, font_u_large_width, font_u_large_height },
    { 'v', font_v_large_bits, font_v_large_width, font_v_large_height },
    { 'w', font_w_large_bits, font_w_large_width, font_w_large_height },
    { 'z', font_z_large_bits, font_z_large_width, font_z_large_height }
};

const Bitmap font_small[17] = 
{
    { '0', font_0_small_bits, font_0_small_width, font_0_small_height },
    { '1', font_1_small_bits, font_1_small_width, font_1_small_height },
    { '2', font_2_small_bits, font_2_small_width, font_2_small_height },
    { '3', font_3_small_bits, font_3_small_width, font_3_small_height },
    { '4', font_4_small_bits, font_4_small_width, font_4_small_height },
    { '5', font_5_small_bits, font_5_small_width, font_5_small_height },
    { '6', font_6_small_bits, font_6_small_width, font_6_small_height },
    { '7', font_7_small_bits, font_7_small_width, font_7_small_height },
    { '8', font_8_small_bits, font_8_small_width, font_8_small_height },
    { '9', font_9_small_bits, font_9_small_width, font_9_small_height },
    { 'b', font_b_small_bits, font_b_small_width, font_b_small_height },
    { 'C', font_C_small_bits, font_C_small_width, font_C_small_height },
    { '-', font_dash_small_bits, font_dash_small_width, font_dash_small_height },
    { '°', font_degree_small_bits, font_degree_small_width, font_degree_small_height },
    { 'f', font_f_small_bits, font_f_small_width, font_f_small_height },
    { 'm', font_m_small_bits, font_m_small_width, font_m_small_height },
    { 't', font_t_small_bits, font_t_small_width, font_t_small_height }
};

const Bitmap icons[30] = 
{
    { 'n', arrow_n_bits, arrow_n_width, arrow_n_height },
    { 'no', arrow_no_bits, arrow_no_width, arrow_no_height },
    { 'nw', arrow_nw_bits, arrow_nw_width, arrow_nw_height },
    { 'o', arrow_o_bits, arrow_o_width, arrow_o_height },
    { 'w', arrow_w_bits, arrow_w_width, arrow_w_height },
    { 'z', arrow_z_bits, arrow_z_width, arrow_z_height },
    { 'zo', arrow_zo_bits, arrow_zo_width, arrow_zo_height },
    { 'zw', arrow_zw_bits, arrow_zw_width, arrow_zw_height },
    { 'co2', icon_co2_bits, icon_co2_width, icon_co2_height },
    { 'humid', icon_humid_bits, icon_humid_width, icon_humid_height },
    { 'pres', icon_pres_bits, icon_pres_width, icon_pres_height },
    { 'temp', icon_temp_bits, icon_temp_width, icon_temp_height },
    { 'clouded', weather_clouded_bits, weather_clouded_width, weather_clouded_height },
    { 'fog', weather_fog_bits, weather_fog_width, weather_fog_height },
    { 'lightning', weather_lightning_bits, weather_lightning_width, weather_lightning_height },
    { 'night', weather_night_bits, weather_night_width, weather_night_height },
    { 'nightclouded', weather_nightclouded_bits, weather_nightclouded_width, weather_nightclouded_height },
    { 'nightfog', weather_nightfog_bits, weather_nightfog_width, weather_nightfog_height },
    { 'nightlightning', weather_nightlightning_bits, weather_nightlightning_width, weather_nightlightning_height },
    { 'nightrain', weather_nightrain_bits, weather_nightrain_width, weather_nightrain_height },
    { 'nightsnow', weather_nightsnow_bits, weather_nightsnow_width, weather_nightsnow_height },
    { 'rain', weather_rain_bits, weather_rain_width, weather_rain_height },
    { 'snow', weather_snow_bits, weather_snow_width, weather_snow_height },
    { 'sunny', weather_sunny_bits, weather_sunny_width, weather_sunny_height },
    { 'sunnyclouded', weather_sunnyclouded_bits, weather_sunnyclouded_width, weather_sunnyclouded_height },
    { 'sunnyfog', weather_sunnyfog_bits, weather_sunnyfog_width, weather_sunnyfog_height },
    { 'sunnylightning', weather_sunnylightning_bits, weather_sunnylightning_width, weather_sunnylightning_height },
    { 'sunnyrain', weather_sunnyrain_bits, weather_sunnyrain_width, weather_sunnyrain_height },
    { 'sunnysnow', weather_sunnysnow_bits, weather_sunnysnow_width, weather_sunnysnow_height },
    { 'unknown', weather_unknown_bits, weather_unknown_width, weather_unknown_height }
};


Bitmap getBitmapLarge(char character)
{
    for (int i = 0; i < 40; i++)
        if (strcmp(character, font_large[i].name) == 0)
            return font_large[i];
}

Bitmap getBitmapSmall(char character)
{
    for (int i = 0; i < 17; i++)
        if (strcmp(character, font_small[i].name) == 0)
            return font_small[i];
}

Bitmap getBitmapIcon(char* name)
{
    for (int i = 0; i < 30; i++)
        if (strcmp(name, icons[i].name) == 0)
            return icons[i];
}
