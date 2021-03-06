/**
 * @file Misaka_rgb_bling.c
 * @brief
 * @author xqyjlj (xqyjlj@126.com)
 * @version 0.0
 * @date 2021-08-01
 * @copyright Copyright © 2020-2021 xqyjlj<xqyjlj@126.com>
 *
 * *********************************************************************************
 * @par ChangeLog:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2021-08-01 <td>0.0     <td>xqyjlj  <td>内容
 * </table>
 * *********************************************************************************
 */
#include "Misaka_rgb_bling.h"

static Misaka_RGB_Bling_Struct s_Misaka_RGB_Bling = {0};

/**
 * @brief Misaka_RGB_Bling初始化
 */
void Misaka_rgb_bling_init(uint16_t base)
{
    s_Misaka_RGB_Bling.color1 = Misaka_RGB_Bling_Color_None;
    s_Misaka_RGB_Bling.color2 = Misaka_RGB_Bling_Color_None;
    s_Misaka_RGB_Bling.contiune_time = 0;
    s_Misaka_RGB_Bling.color1_cnt = 0;
    s_Misaka_RGB_Bling.period_cnt = 0;
    s_Misaka_RGB_Bling.cnt = 0;
    s_Misaka_RGB_Bling.time_base = base;
    s_Misaka_RGB_Bling.endless_flag = 0;
    Misaka_set_bling_pin(Misaka_RGB_Bling_Color_None);
}

/**
 * @brief                   Misaka_RGB_Bling模式设置
 * @param  color1           颜色1
 * @param  color2           颜色2
 * @param  color1_time      颜色1时间
 * @param  color2_time      颜色2时间
 * @param  cnt              次数
 * @param  endless_flag     无尽模式
 */
void Misaka_rgb_bling_mode_set(Misaka_RGB_Bling_Color_Enum color1,
                               Misaka_RGB_Bling_Color_Enum color2,
                               uint32_t color1_time,
                               uint32_t color2_time,
                               uint16_t cnt,
                               uint8_t endless_flag)
{
    s_Misaka_RGB_Bling.color1 = color1;
    s_Misaka_RGB_Bling.color2 = color2;
    s_Misaka_RGB_Bling.color1_cnt = color1_time / s_Misaka_RGB_Bling.time_base;
    s_Misaka_RGB_Bling.period_cnt = s_Misaka_RGB_Bling.color1_cnt + (color2_time / s_Misaka_RGB_Bling.time_base);
    s_Misaka_RGB_Bling.cnt = cnt;
    s_Misaka_RGB_Bling.contiune_time = cnt * s_Misaka_RGB_Bling.period_cnt;
    s_Misaka_RGB_Bling.endless_flag = endless_flag;
}

/**
 * @brief   周期处理函数
 */
void Misaka_rgb_bling_cycle_process()
{
    if (s_Misaka_RGB_Bling.contiune_time >= 1)
    {
        s_Misaka_RGB_Bling.contiune_time--;
    }
    else
    {
        Misaka_set_bling_pin(Misaka_RGB_Bling_Color_None);
    }

    if (s_Misaka_RGB_Bling.contiune_time != 0 //总时间未清0
            || s_Misaka_RGB_Bling.endless_flag == 1) //判断无尽模式是否开启
    {
        s_Misaka_RGB_Bling.cnt++;
        if (s_Misaka_RGB_Bling.cnt <= s_Misaka_RGB_Bling.color1_cnt)
        {
            Misaka_set_bling_pin(s_Misaka_RGB_Bling.color1);
        }
        else if (s_Misaka_RGB_Bling.cnt > s_Misaka_RGB_Bling.color1_cnt && s_Misaka_RGB_Bling.cnt <= s_Misaka_RGB_Bling.period_cnt)
        {
            Misaka_set_bling_pin(s_Misaka_RGB_Bling.color2);
        }
        else
        {
            s_Misaka_RGB_Bling.cnt = 0;
        }
    }
}


