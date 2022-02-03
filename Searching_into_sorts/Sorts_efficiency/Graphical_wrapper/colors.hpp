#ifndef COLORS_USED
#define COLORS_USED

const unsigned char MAX_COLOR_VALUE = 255;

struct HSV
{
	int h;
	int s;
	int v;

	int get_h() const { return h; }
	int get_s() const { return s; }
	int get_v() const { return v; }

	void set_h(int par_h) { h = par_h; }
	void set_s(int par_s) { s = par_s; }
	void set_v(int par_v) { v = par_v; }
};

struct HSV_d
{
	double h;
	double s;
	double v;
};


struct Color_d
{
	double r;
	double g;
	double b;
};

struct Color 
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;

	unsigned char get_a() const { return a; }
	unsigned char get_r() const { return r; }
	unsigned char get_g() const { return g; }
	unsigned char get_b() const { return b; }

	void set_a(unsigned char par_a) { a = par_a; }
	void set_r(unsigned char par_r) { r = par_r; }
	void set_g(unsigned char par_g) { g = par_g; }
	void set_b(unsigned char par_b) { b = par_b; }

	friend bool operator==(const Color &left, const Color &right)
	{
		if (left.a == right.a && left.r == right.r && left.g == right.g && left.b == right.b)
			return true;

		return false;
	}

	friend bool operator!=(const Color &left, const Color &right)
	{
		if (left.a != right.a || left.r != right.r || left.g != right.g || left.b != right.b)
			return true;

		return false;
	}

	const Color operator*=(const double value)
	{
		r = double(r) * value;
		g = double(g) * value;
		b = double(b) * value;

		return *this;
	}

	const Color operator/=(const double value)
	{
		if (value == 0)
			return *this;

		r = double(r) / value;
		g = double(g) / value;
		b = double(b) / value;

		return *this;
	}

	// friend Color operator+(const Color &left, const Color &right)
	// {
	// 	Color color_sum = {}MAX_COLOR_VALUE, left.get_r() + right.get_r(), left.get_g() + right.get_g(), left.get_b() + right.get_b());
	// }
};



const Color BLACK  = { 0, 0, 0, 255 };
const Color WHITE  = { 255, 255, 255, 255 };
const Color RED    = { 255, 0, 0, 255 };
const Color GREEN  = { 0, 255, 0, 255 };
const Color BLUE   = { 0, 0, 255, 255 };
const Color YELLOW = { 255, 255, 0, 255 };
const Color PURPLE = { 128, 0, 128, 255 };
const Color FUCHSIA = { 255, 0, 255, 255 };
const Color CYAN = { 0, 255, 255, 255 };
const Color MEDIUM_PURPLE = { 147, 112, 219, 255 };
const Color DARK_GREY = { 32, 32, 32, 255 };
const Color MEDIUM_GREY = { 100, 100, 100, 255 };
const Color GREY = { 182, 182, 182, 255 };
const Color TRANSPARENT = { 0, 0, 0, 0 };
const Color GENTLE_ORANGE = { 255, 161, 74, 255 };


HSV get_hsv(const Color &rgb);
Color get_rgb(const HSV &hsv);

#endif // COLORS_USED
