#include "colors.hpp"

HSV get_hsv(const Color &rgb)
{
	HSV hsv = { 0, 0, 0 };
    unsigned char rgbMin = 0;
    unsigned char rgbMax = 0;

    rgbMin = rgb.get_r() < rgb.get_g() ? (rgb.get_r() < rgb.get_b() ? rgb.get_r() : rgb.get_b()) : (rgb.get_g() < rgb.get_b() ? rgb.get_g() : rgb.get_b());
    rgbMax = rgb.get_r() > rgb.get_g() ? (rgb.get_r() > rgb.get_b() ? rgb.get_r() : rgb.get_b()) : (rgb.get_g() > rgb.get_b() ? rgb.get_g() : rgb.get_b());

    hsv.set_v(rgbMax);
   
    if (hsv.get_v() == 0)
    {
        hsv.set_h(0);
        hsv.set_s(0);
        return hsv;
    }

    hsv.set_s((unsigned)(255.0 * (1.0 - (double)rgbMin / (double)rgbMax)));
    if (hsv.get_s() == 0)
    {
        hsv.set_h(0);
        return hsv;
    }

    if (rgbMax == rgb.get_r())
        if (rgb.get_g() >= rgb.get_b())
        	hsv.set_h(0 + 43 * ((double)(rgb.get_g()) - (double)(rgb.get_b())) / ((double)rgbMax - (double)rgbMin));
        else
        {
        	hsv.set_h(255 + 43 * ((double)rgb.get_g() - (double)rgb.get_b()) / ((double)rgbMax - (double)rgbMin));
        }
    else if (rgbMax == rgb.get_g())
        hsv.set_h((unsigned)(85 + 43 * ((double)rgb.get_b() - (double)rgb.get_r()) / ((double)rgbMax - (double)rgbMin)));
    else
        hsv.set_h((unsigned)(171 + 43 * ((double)rgb.get_r() - (double)rgb.get_g()) / ((double)rgbMax - (double)rgbMin)));

    return hsv;
}

Color get_rgb(const HSV &hsv)
{
	Color rgb = { 0, 0, 0, 255 };
    unsigned char region = 0; 
    unsigned char remainder = 0;
    unsigned char p = 0;
    unsigned char q = 0;
    unsigned char t = 0;

    if (hsv.get_s() == 0)
    {
        rgb.set_r(hsv.get_v());
        rgb.set_g(hsv.get_v());
        rgb.set_b(hsv.get_v());
        
        return rgb;
    }

    double region_d = ((double)hsv.get_h() / 43);
    region = (unsigned char)region_d;
    // printf("region %u\n", region);
    remainder = (unsigned char)(((double)hsv.get_h() - ((double)region * 43)) * 6); 

    p = (hsv.get_v() * (255 - hsv.get_s())) >> 8;
    q = (hsv.get_v() * (255 - ((hsv.get_s() * remainder) >> 8))) >> 8;
    t = (hsv.get_v() * (255 - ((hsv.get_s() * (255 - remainder)) >> 8))) >> 8;

    switch (region)
    {
        case 0:
            rgb.set_r(hsv.get_v()); 
            rgb.set_g(t); 
            rgb.set_b(p);
            
            break;
		case 1:
            
            rgb.set_r(q); 
            rgb.set_g(hsv.get_v()); 
            rgb.set_b(p);
            
            break;
        case 2:
            
            rgb.set_r(p); 
            rgb.set_g(hsv.get_v()); 
            rgb.set_b(t);
            
            break;
        case 3:
            
            rgb.set_r(p); 
            rgb.set_g(q); 
            rgb.set_b(hsv.get_v());
            
            break;
        case 4:
            
            rgb.set_r(t); 
            rgb.set_g(p); 
            rgb.set_b(hsv.get_v());
            
            break;
        default:
            
            rgb.set_r(hsv.get_v()); 
            rgb.set_g(p); 
            rgb.set_b(q);
            
            break;
    }

    return rgb;
}
