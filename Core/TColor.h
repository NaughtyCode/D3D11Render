#pragma once

inline float FClamp( FLOAT X, FLOAT Min, FLOAT Max )
{
	return X<Min ? Min : X<Max ? X : Max;
}

template <typename T> struct TColor;
typedef TColor<UINT8> ColorB;
typedef TColor<FLOAT> ColorF;

template <typename T>
struct TColor
{
	T r,g,b,a;
	
	inline TColor()
	{
		
	};
	
	inline TColor(T _x, T _y, T _z, T _w);
	inline TColor(T _x, T _y, T _z);
	
	inline TColor(const unsigned int abgr );
	inline TColor(const FLOAT c );
	inline TColor(const ColorF& c);
	inline TColor(const ColorF& c, float fAlpha);

	void Clamp(float Min = 0, float Max = 1.0f)  
	{
		r = ::FClamp(r, Min, Max);
		g = ::FClamp(g, Min, Max);
		b = ::FClamp(b, Min, Max);
		a = ::FClamp(a, Min, Max);
	}
	
	void ScaleCol (float f)	
	{
		r = static_cast<T>(r * f); g = static_cast<T>(g * f); b = static_cast<T>(b * f);
	}

	float Luminance() const	
	{
		return r*0.30f + g*0.59f + b*0.11f;
	}

	inline float Max() const
	{
		return max(r, max(b, g));
	}

	float NormalizeCol (ColorF& out) const
	{
		float max = Max();

		if (max == 0)
			return 0;

		out = *this / max;

		return max;
	}
	
	inline TColor& operator = (const TColor &c)
	{
		r=(T)c.r;
		g=(T)c.g;
		b=(T)c.b;
		a=(T)c.a;
		return *this;
	}
	
	inline T &operator [] (int index)
	{
		assert(index>=0 && index<=3);
		return ((T*)this)[index];
	}
	
	inline T operator [] (int index) const
	{
		assert(index>=0 && index<=3);
		return ((T*)this)[index];
	}
	
	inline void Set(float fR,float fG,float fB,float fA=1.0f)
	{
		r=static_cast<T>(fR);
		g=static_cast<T>(fG);
		b=static_cast<T>(fB);
		a=static_cast<T>(fA);
	}
	
	inline void set(T _x, T _y = 0, T _z = 0, T _w = 0)
	{
		r = _x; g = _y; b = _z; a = _w;
	}
	
	inline void set(T _x, T _y = 0, T _z = 0)
	{
		r = _x; g = _y; b = _z; a = 1;
	}
	
	inline TColor operator + () const
	{
		return *this;
	}
	
	inline TColor operator - () const
	{
		return TColor<T>(-r, -g, -b, -a);
	}
	
	inline TColor & operator += (const TColor & v)
	{
		T _r = r, _g = g, _b = b, _a = a;
		_r += v.r;
		_g += v.g;
		_b += v.b;
		_a += v.a;
		
		r = _r;
		g = _g;
		b = _b;
		a = _a;
		
		return *this;
	}
	
	inline TColor & operator -= (const TColor & v)
	{
		r -= v.r; g -= v.g; b -= v.b; a -= v.a;
		return *this;
	}
	
	inline TColor & operator *= (const TColor & v)
	{
		r *= v.r; g *= v.g; b *= v.b; a *= v.a;
		return *this;
	}
	
	inline TColor & operator /= (const TColor & v)
	{
		r /= v.r; g /= v.g; b /= v.b; a /= v.a;
		return *this;
	}
	
	inline TColor & operator *= (T s)
	{
		r *= s; g *= s; b *= s; a *= s;
		return *this;
	}
	
	inline TColor & operator /= (T s)
	{
		s = 1.0f / s;
		r *= s; g *= s; b *= s; a *= s;
		return *this;
	}
	
	inline TColor operator + (const TColor & v) const
	{
		return TColor(r + v.r, g + v.g, b + v.b, a + v.a);
	}
	
	inline TColor operator - (const TColor & v) const
	{
		return TColor(r - v.r, g - v.g, b - v.b, a - v.a);
	}
	
	inline TColor operator * (const TColor & v) const
	{
		return TColor(r * v.r, g * v.g, b * v.b, a * v.a);
	}
	
	inline TColor operator / (const TColor & v) const
	{
		return TColor(r / v.r, g / v.g, b / v.b, a / v.a);
	}
	
	inline TColor operator * (T s) const
	{
		return TColor(r * s, g * s, b * s, a * s);
	}
	
	inline TColor operator / (T s) const
	{
		s = 1.0f / s;
		return TColor(r * s, g * s, b * s, a * s);
	}
	
	inline bool operator == (const TColor & v) const
	{
		return (r == v.r) && (g == v.g) && (b == v.b) && (a == v.a);
	}
	
	inline bool operator != (const TColor & v) const
	{
		return (r != v.r) || (g != v.g) || (b != v.b) || (a != v.a);
	}
	
	inline unsigned char pack_rgb332() const;
	inline unsigned short pack_argb4444() const;
	inline unsigned short pack_rgb555() const;
	inline unsigned short pack_rgb565() const;
	inline unsigned int pack_bgr888() const;
	inline unsigned int pack_rgb888() const;
	inline unsigned int pack_abgr8888() const;
	inline unsigned int pack_argb8888() const;
	
	inline void toHSV(FLOAT &h, FLOAT &s, FLOAT&v) const;
	inline void fromHSV(FLOAT h, FLOAT s, FLOAT v);
	
	inline void clamp(T bottom = 0.0f, T top = 1.0f);

	inline void maximum(const TColor<T> &ca, const TColor<T> &cb);
	inline void minimum(const TColor<T> &ca, const TColor<T> &cb);
	inline void abs();

	inline void adjust_contrast(T c);
	inline void adjust_saturation(T s);

	inline void lerpFloat(const TColor<T> &ca, const TColor<T> &cb, float s);
	inline void negative(const TColor<T> &c);
	inline void grey(const TColor<T> &c);
	
	static inline UINT ComputeAvgTColorFast( const UINT dwCol0, const UINT dwCol1 )
	{
		UINT dwHalfCol0 = (dwCol0/2) & 0x7f7f7f7f;
		UINT dwHalfCol1 = (dwCol1/2) & 0x7f7f7f7f;

		return dwHalfCol0+dwHalfCol1;
	}
	
	TColor<T> RGB2mCIE() const
	{
		TColor<T> in=*this;

		// to get grey chrominance for dark colors
		in.r+=0.000001f;
		in.g+=0.000001f;
		in.b+=0.000001f;

		float RGBSum = in.r+in.g+in.b;		

		float fInv = 1.0f / RGBSum;

		float RNorm = 3*10.0f/31.0f*in.r * fInv;
		float GNorm = 3*21.0f/63.0f*in.g * fInv;
		float Scale = RGBSum/3.0f;
		
		RNorm = max(0.0f, min(1.0f, RNorm));
		GNorm = max(0.0f, min(1.0f, GNorm));

		return TColor<T>(RNorm, GNorm, Scale);
	}
	
	TColor<T> mCIE2RGB() const
	{
		TColor<T> out = *this;
		float fScale = out.b;
		out.r *= 31.0f/30.0f;
		out.g *= 63.0f/63.0f;
		out.b = 0.999f-out.r-out.g;
		float s = 3.0f*fScale;
		out.r*=s; out.g*=s; out.b*=s;
		out.Clamp();
		return out;
	}
	
	void rgb2srgb()
	{
		for(int i=0; i<3; i++)
		{
		T & c = (*this)[i];
		
		if( c < 0.0031308f ) 
		{ 
		c = 12.92f * c; 
		} 
		else 
		{ 
		c = 1.055f * pow( c, 1.0f/2.4f ) - 0.055f; 
		} 
		}
	}
	
	void srgb2rgb()
	{
		for(int i=0; i<3; i++)
		{
			T & c = (*this)[i];
		      
			if( c <= 0.040448643f )
			{ 
			  c = c/12.92f; 
			} 
			else 
			{ 
			  c = pow( ( c + 0.055f) / 1.055f, 2.4f ); 
			} 
		}
	}
	
	void GetMemoryUsage( class ICrySizer *pSizer ) const
	{
		
	}
	
};

template<>
inline TColor<FLOAT>::TColor(FLOAT _x, FLOAT _y, FLOAT _z, FLOAT _w)	
{
	r = _x; g = _y; b = _z; a = _w;
}

template<>
inline TColor<FLOAT>::TColor(FLOAT _x, FLOAT _y, FLOAT _z)
{
	r = _x; g = _y; b = _z; a = 1.f;
}

template<>
inline TColor<UINT8>::TColor(UINT8 _x, UINT8 _y, UINT8 _z, UINT8 _w)
{
	r = _x; g = _y; b = _z; a = _w;
}

template<>
inline TColor<UINT8>::TColor(UINT8 _x, UINT8 _y, UINT8 _z)
{
	r = _x; g = _y; b = _z; a = 255;
}



template<>
inline TColor<FLOAT>::TColor(const unsigned int abgr)	
{
	r = (abgr & 0xff) / 255.0f;
	g = ((abgr>>8) & 0xff) / 255.0f;
	b = ((abgr>>16) & 0xff) / 255.0f;
	a = ((abgr>>24) & 0xff) / 255.0f;
}

template<>
inline TColor<UINT8>::TColor(const unsigned int c)
{
	*(unsigned int*)(&r)=c;
}

template<>
inline TColor<FLOAT>::TColor(const float c)	
{
	r=c;	g=c;	b=c;	a=c;
}
template<>
inline TColor<UINT8>::TColor(const float c)	
{
	r = (UINT8)(c*255);	g = (UINT8)(c*255);	b = (UINT8)(c*255);	a = (UINT8)(c*255);
}


template<>
inline TColor<FLOAT>::TColor(const ColorF& c)	
{
	r=c.r;	g=c.g;	b=c.b;	a=c.a;
}
template<>
inline TColor<UINT8>::TColor(const ColorF& c)	{
	r = (UINT8)(c.r*255);	g = (UINT8)(c.g*255);	b = (UINT8)(c.b*255);	a = (UINT8)(c.a*255);
}

template<>
inline TColor<FLOAT>::TColor(const ColorF& c, float fAlpha)
{
	r=c.r;	g=c.g;	b=c.b;	a=fAlpha;
}

template <class T>
inline TColor<T> operator * (T s, const TColor<T> & v)
{
	return TColor<T>(v.r * s, v.g * s, v.b * s, v.a * s);
}

template <class T>
inline unsigned char TColor<T>::pack_rgb332() const
{
	unsigned char cr;
	unsigned char cg;
	unsigned char cb;
	if(sizeof(r) == 1) // char and unsigned char
	{
		cr = (unsigned char)r;
		cg = (unsigned char)g;
		cb = (unsigned char)b;
	}
	else if(sizeof(r) == 2) // short and unsigned short
	{
		cr = (unsigned short)(r)>>8;
		cg = (unsigned short)(g)>>8;
		cb = (unsigned short)(b)>>8;
	}
	else // float or double
	{
		cr = (unsigned char)(r * 255.0f);
		cg = (unsigned char)(g * 255.0f);
		cb = (unsigned char)(b * 255.0f);
	}
	return ((cr >> 5) << 5) | ((cg >> 5) << 2) | (cb >> 5);
}

template <class T>
inline unsigned short TColor<T>::pack_argb4444() const
{
	unsigned char cr;
	unsigned char cg;
	unsigned char cb;
	unsigned char ca;
	if(sizeof(r) == 1) // char and unsigned char
	{
		cr = (unsigned char)r;
		cg = (unsigned char)g;
		cb = (unsigned char)b;
		ca = (unsigned char)a;
	}
	else if(sizeof(r) == 2) // short and unsigned short
	{
		cr = (unsigned short)(r)>>8;
		cg = (unsigned short)(g)>>8;
		cb = (unsigned short)(b)>>8;
		ca = (unsigned short)(a)>>8;
	}
	else // float or double
	{
		cr = (unsigned char)(r * 255.0f);
		cg = (unsigned char)(g * 255.0f);
		cb = (unsigned char)(b * 255.0f);
		ca = (unsigned char)(a * 255.0f);
	}
	return ((ca >> 4) << 12) | ((cr >> 4) << 8) | ((cg >> 4) << 4) | (cb >> 4);
}

template <class T>
inline unsigned short TColor<T>::pack_rgb555() const
{
	unsigned char cr;
	unsigned char cg;
	unsigned char cb;
	if(sizeof(r) == 1) // char and unsigned char
	{
		cr = (unsigned char)r;
		cg = (unsigned char)g;
		cb = (unsigned char)b;
	}
	else if(sizeof(r) == 2) // short and unsigned short
	{
		cr = (unsigned short)(r)>>8;
		cg = (unsigned short)(g)>>8;
		cb = (unsigned short)(b)>>8;
	}
	else // float or double
	{
		cr = (unsigned char)(r * 255.0f);
		cg = (unsigned char)(g * 255.0f);
		cb = (unsigned char)(b * 255.0f);
	}
	return ((cr >> 3) << 10) | ((cg >> 3) << 5) | (cb >> 3);
}


template <class T>
inline unsigned short TColor<T>::pack_rgb565() const
{
	unsigned short cr;
	unsigned short cg;
	unsigned short cb;
	if(sizeof(r) == 1) // char and unsigned char
	{
		cr = (unsigned short)r;
		cg = (unsigned short)g;
		cb = (unsigned short)b;
	}
	else if(sizeof(r) == 2) // short and unsigned short
	{
		cr = (unsigned short)(r)>>8;
		cg = (unsigned short)(g)>>8;
		cb = (unsigned short)(b)>>8;
	}
	else // float or double
	{
		cr = (unsigned short)(r * 255.0f);
		cg = (unsigned short)(g * 255.0f);
		cb = (unsigned short)(b * 255.0f);
	}
	return ((cr >> 3) << 11) |	((cg >> 2) << 5) | (cb >> 3);
}


template <class T>
inline unsigned int TColor<T>::pack_bgr888() const
{
	unsigned char cr;
	unsigned char cg;
	unsigned char cb;
	if(sizeof(r) == 1) // char and unsigned char
	{
		cr = (unsigned char)r;
		cg = (unsigned char)g;
		cb = (unsigned char)b;
	}
	else if(sizeof(r) == 2) // short and unsigned short
	{
		cr = (unsigned short)(r)>>8;
		cg = (unsigned short)(g)>>8;
		cb = (unsigned short)(b)>>8;
	}
	else // float or double
	{
		cr = (unsigned char)(r * 255.0f);
		cg = (unsigned char)(g * 255.0f);
		cb = (unsigned char)(b * 255.0f);
	}
	return (cb << 16) | (cg << 8) | cr;
}


template <class T>
inline unsigned int TColor<T>::pack_rgb888() const
{
	unsigned char cr;
	unsigned char cg;
	unsigned char cb;
	if(sizeof(r) == 1) // char and unsigned char
	{
		cr = (unsigned char)r;
		cg = (unsigned char)g;
		cb = (unsigned char)b;
	}
	else if(sizeof(r) == 2) // short and unsigned short
	{
		cr = (unsigned short)(r)>>8;
		cg = (unsigned short)(g)>>8;
		cb = (unsigned short)(b)>>8;
	}
	else // float or double
	{
		cr = (unsigned char)(r * 255.0f);
		cg = (unsigned char)(g * 255.0f);
		cb = (unsigned char)(b * 255.0f);
	}
	return (cr << 16) | (cg << 8) | cb;
}


template <class T>
inline unsigned int TColor<T>::pack_abgr8888() const
{
	unsigned char cr;
	unsigned char cg;
	unsigned char cb;
	unsigned char ca;
	if(sizeof(r) == 1) // char and unsigned char
	{
		cr = (unsigned char)r;
		cg = (unsigned char)g;
		cb = (unsigned char)b;
		ca = (unsigned char)a;
	}
	else if(sizeof(r) == 2) // short and unsigned short
	{
		cr = (unsigned short)(r)>>8;
		cg = (unsigned short)(g)>>8;
		cb = (unsigned short)(b)>>8;
		ca = (unsigned short)(a)>>8;
	}
	else // float or double
	{
		cr = (unsigned char)(r * 255.0f);
		cg = (unsigned char)(g * 255.0f);
		cb = (unsigned char)(b * 255.0f);
		ca = (unsigned char)(a * 255.0f);
	}
	return (ca << 24) | (cb << 16) | (cg << 8) | cr;
}



template <class T>
inline unsigned int TColor<T>::pack_argb8888() const
{
	unsigned char cr;
	unsigned char cg;
	unsigned char cb;
	unsigned char ca;
	if(sizeof(r) == 1) // char and unsigned char
	{
		cr = (unsigned char)r;
		cg = (unsigned char)g;
		cb = (unsigned char)b;
		ca = (unsigned char)a;
	}
	else if(sizeof(r) == 2) // short and unsigned short
	{
		cr = (unsigned short)(r)>>8;
		cg = (unsigned short)(g)>>8;
		cb = (unsigned short)(b)>>8;
		ca = (unsigned short)(a)>>8;
	}
	else // float or double
	{
		cr = (unsigned char)(r * 255.0f);
		cg = (unsigned char)(g * 255.0f);
		cb = (unsigned char)(b * 255.0f);
		ca = (unsigned char)(a * 255.0f);
	}
	return (ca << 24) | (cr << 16) | (cg << 8) | cb;
}


template <class T>
inline void TColor<T>::toHSV(FLOAT &h, FLOAT &s, FLOAT&v) const
{
	FLOAT r, g, b;
	if (sizeof(this->r) == 1) // 8bit integer
	{
		r = this->r * (1.0f / FLOAT(0xff));
		g = this->g * (1.0f / FLOAT(0xff));
		b = this->b * (1.0f / FLOAT(0xff));
	}
	else if (sizeof(this->r) == 2) // 16bit integer
	{
		r = this->r * (1.0f / FLOAT(0xffff));
		g = this->g * (1.0f / FLOAT(0xffff));
		b = this->b * (1.0f / FLOAT(0xffff));
	}
	else // floating point
	{
		r = this->r;
		g = this->g;
		b = this->b;
	}

	if ((b > g) && (b > r))
	{
		if (!::iszero(v = b))
		{
			const FLOAT min = r < g ? r : g;
			const FLOAT delta = v - min;
			if (!::iszero(delta))
			{
				s = delta / v;
				h = (240.0f/360.0f) + (r - g) / delta * (60.0f/360.0f);
			}
			else
			{
				s = 0.0f;
				h = (240.0f/360.0f) + (r - g) * (60.0f/360.0f);
			}
			if (h < 0.0f) h += 1.0f;
		}
		else
		{
			s = 0.0f;
			h = 0.0f;
		}
	}
	else if (g > r)
	{
		if (!::iszero(v = g))
		{
			const FLOAT min = r < b ? r : b;
			const FLOAT delta = v - min;
			if (!::iszero(delta))
			{
				s = delta / v;
				h = (120.0f/360.0f) + (b - r) / delta * (60.0f/360.0f);
			}
			else
			{
				s = 0.0f;
				h = (120.0f/360.0f) + (b - r) * (60.0f/360.0f);
			}
			if (h < 0.0f) h += 1.0f;
		}
		else
		{
			s = 0.0f;
			h = 0.0f;
		}
	}
	else
	{
		if (!::iszero(v = r))
		{
			const FLOAT min = g < b ? g : b;
			const FLOAT delta = v - min;
			if (!::iszero(delta))
			{
				s = delta / v;
				h = (g - b) / delta * (60.0f/360.0f);
			}
			else
			{
				s = 0.0f;
				h = (g - b) * (60.0f/360.0f);
			}
			if (h < 0.0f) h += 1.0f;
		}
		else
		{
			s = 0.0f;
			h = 0.0f;
		}
	}
}


template <class T>
inline void TColor<T>::fromHSV(FLOAT h, FLOAT s, FLOAT v)
{
	FLOAT r, g, b;
	if (::iszero(v))
	{
		r = 0.0f; g = 0.0f; b = 0.0f;
	}
	else if (::iszero(s))
	{
		r = v; g = v; b = v;
	}
	else
	{
		const FLOAT hi = h * 6.0f;
		const int32 i = (int32)::floor(hi);
		const FLOAT f = hi - i;

		const FLOAT v0 = v * (1.0f - s);
		const FLOAT v1 = v * (1.0f - s * f);
		const FLOAT v2 = v * (1.0f - s * (1.0f - f));

		switch (i)
		{
		case 0: r = v; g = v2; b = v0; break;
		case 1: r = v1; g = v; b = v0; break;
		case 2: r = v0; g = v; b = v2; break;
		case 3: r = v0; g = v1; b = v; break;
		case 4: r = v2; g = v0; b = v; break;
		case 5: r = v; g = v0; b = v1; break;

		case 6: r = v; g = v2; b = v0; break;
		case -1: r = v; g = v0; b = v1; break;
		default: r = 0.0f; g = 0.0f; b = 0.0f; break;
		}
	}
	
	if (sizeof(this->r) == 1) // 8bit integer
	{
		this->r = r * FLOAT(0xff);
		this->g = g * FLOAT(0xff);
		this->b = b * FLOAT(0xff);
	}
	else if (sizeof(this->r) == 2) // 16bit integer
	{
		this->r = r * FLOAT(0xffff);
		this->g = g * FLOAT(0xffff);
		this->b = b * FLOAT(0xffff);
	}
	else // floating point
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}
}


template <class T>
inline void TColor<T>::clamp(T bottom, T top)
{
	r = min(top, max(bottom, r));
	g = min(top, max(bottom, g));
	b = min(top, max(bottom, b));
	a = min(top, max(bottom, a));
}


template <class T>
inline void TColor<T>::maximum(const TColor<T> &ca, const TColor<T> &cb)
{
	r = max(ca.r, cb.r);
	g = max(ca.g, cb.g);
	b = max(ca.b, cb.b);
	a = max(ca.a, cb.a);
}


template <class T>
inline void TColor<T>::minimum(const TColor<T> &ca, const TColor<T> &cb)
{
	r = min(ca.r, cb.r);
	g = min(ca.g, cb.g);
	b = min(ca.b, cb.b);
	a = min(ca.a, cb.a);
}


template <class T>
inline void TColor<T>::abs()
{
	r = cry_fabsf(r);
	g = cry_fabsf(g);
	b = cry_fabsf(b);
	a = cry_fabsf(a);
}


template <class T>
inline void TColor<T>::adjust_contrast(T c)
{
	r = 0.5f + c * (r - 0.5f);
	g = 0.5f + c * (g - 0.5f);
	b = 0.5f + c * (b - 0.5f);
	a = 0.5f + c * (a - 0.5f);
}

template <class T>
inline void TColor<T>::adjust_saturation(T s)
{
	T grey = r * 0.2125f + g * 0.7154f + b * 0.0721f;    
	r = grey + s * (r - grey);
	g = grey + s * (g - grey);
	b = grey + s * (b - grey);
	a = grey + s * (a - grey);
}


template <class T>
inline void TColor<T>::lerpFloat(const TColor<T> &ca, const TColor<T> &cb, float s)
{
	r = (T)(ca.r + s * (cb.r - ca.r));
	g = (T)(ca.g + s * (cb.g - ca.g));
	b = (T)(ca.b + s * (cb.b - ca.b));
	a = (T)(ca.a + s * (cb.a - ca.a));
}


template <class T>
inline void TColor<T>::negative(const TColor<T> &c)
{
	r = T(1.0f) - r;
	g = T(1.0f) - g;
	b = T(1.0f) - b;
	a = T(1.0f) - a;
}

template <class T>
inline void TColor<T>::grey(const TColor<T> &c)
{
	T m = (r + g + b) / T(3);

	r = m;
	g = m;
	b = m;
	a = a;
}

#if defined(NEED_ENDIAN_SWAP)
	#define RGBA8(a,b,g,r)     ((UINT)(((UINT8)(r)|((uint16)((UINT8)(g))<<8))|(((UINT)(UINT8)(b))<<16)) | (((UINT)(UINT8)(a))<<24) )
#else
	#define RGBA8(r,g,b,a)     ((UINT)(((UINT8)(r)|((uint16)((UINT8)(g))<<8))|(((UINT)(UINT8)(b))<<16)) | (((UINT)(UINT8)(a))<<24) )
#endif

#define TColorBlack		ColorF (0.0f, 0.0f, 0.0f)
#define TColorWhite		ColorF (1.0f, 1.0f, 1.0f)
#define TColorAquamarine        ColorF (0.439216f, 0.858824f, 0.576471f)
#define TColorBlue		ColorF (0.0f, 0.0f, 1.0f)
#define TColorBlueViolet        ColorF (0.623529f, 0.372549f, 0.623529f)
#define TColorBrown		ColorF (0.647059f, 0.164706f, 0.164706f)
#define TColorCadetBlue		ColorF (0.372549f, 0.623529f, 0.623529f)
#define TColorCoral		ColorF (1.0f, 0.498039f, 0.0f)
#define TColorCornflowerBlue	ColorF (0.258824f, 0.258824f, 0.435294f)
#define TColorCyan		ColorF (0.0f, 1.0f, 1.0f)
#define TColorDarkGray		ColorF (0.5f, 0.5f, 0.5f)
#define TColorDarkGreen		ColorF (0.184314f, 0.309804f, 0.184314f)
#define TColorDarkOliveGreen	ColorF (0.309804f, 0.309804f, 0.184314f)
#define TColorDarkOrchild       ColorF (0.6f, 0.196078f, 0.8f)
#define TColorDarkSlateBlue	ColorF (0.419608f, 0.137255f, 0.556863f)
#define TColorDarkSlateGray	ColorF (0.184314f, 0.309804f, 0.309804f)
#define TColorDarkSlateGrey	ColorF (0.184314f, 0.309804f, 0.309804f)
#define TColorDarkTurquoise	ColorF (0.439216f, 0.576471f, 0.858824f)
#define TColorDarkWood		ColorF (0.05f, 0.01f, 0.005f)
#define TColorDimGray		ColorF (0.329412f, 0.329412f, 0.329412f)
#define TColorDimGrey		ColorF (0.329412f, 0.329412f, 0.329412f)
#define TColorFireBrick		ColorF (0.9f, 0.4f, 0.3f)
#define TColorForestGreen       ColorF (0.137255f, 0.556863f, 0.137255f)
#define TColorGold		ColorF (0.8f, 0.498039f, 0.196078f)
#define TColorGoldenrod		ColorF (0.858824f, 0.858824f, 0.439216f)
#define TColorGray		ColorF (0.752941f, 0.752941f, 0.752941f)
#define TColorGreen		ColorF (0.0f, 1.0f, 0.0f)
#define TColorGreenYellow       ColorF (0.576471f, 0.858824f, 0.439216f)
#define TColorGrey		ColorF (0.752941f, 0.752941f, 0.752941f)
#define TColorIndianRed		ColorF (0.309804f, 0.184314f, 0.184314f)
#define TColorKhaki		ColorF (0.623529f, 0.623529f, 0.372549f)
#define TColorLightBlue		ColorF (0.74902f, 0.847059f, 0.847059f)
#define TColorLightGray		ColorF (0.658824f, 0.658824f, 0.658824f)
#define TColorLightGrey		ColorF (0.658824f, 0.658824f, 0.658824f)
#define TColorLightSteelBlue	ColorF (0.560784f, 0.560784f, 0.737255f)
#define TColorLightWood		ColorF (0.6f, 0.24f, 0.1f)
#define TColorLimeGreen		ColorF (0.196078f, 0.8f, 0.196078f)
#define TColorMagenta		ColorF (1.0f, 0.0f, 1.0f)
#define TColorMaroon		ColorF (0.556863f, 0.137255f, 0.419608f)
#define TColorMedianWood        ColorF (0.3f, 0.12f, 0.03f)
#define TColorMediumAquamarine	ColorF (0.196078f, 0.8f, 0.6f)
#define TColorMediumBlue        ColorF (0.196078f, 0.196078f, 0.8f)
#define TColorMediumForestGreen	ColorF (0.419608f, 0.556863f, 0.137255f)
#define TColorMediumGoldenrod	ColorF (0.917647f, 0.917647f, 0.678431f)
#define TColorMediumOrchid	ColorF (0.576471f, 0.439216f, 0.858824f)
#define TColorMediumSeaGreen	ColorF (0.258824f, 0.435294f, 0.258824f)
#define TColorMediumSlateBlue	ColorF (0.498039f, 0.0f, 1.0f)
#define TColorMediumSpringGreen	ColorF (0.498039f, 1.0f, 0.0f)
#define TColorMediumTurquoise	ColorF (0.439216f, 0.858824f, 0.858824f)
#define TColorMediumVioletRed	ColorF (0.858824f, 0.439216f, 0.576471f)
#define TColorMidnightBlue      ColorF (0.184314f, 0.184314f, 0.309804f)
#define TColorNavy                ColorF (0.137255f, 0.137255f, 0.556863f)
#define TColorNavyBlue            ColorF (0.137255f, 0.137255f, 0.556863f)
#define TColorOrange              ColorF (0.8f, 0.196078f, 0.196078f)
#define TColorOrangeRed           ColorF (0.0f, 0.0f, 0.498039f)
#define TColorOrchid              ColorF (0.858824f, 0.439216f, 0.858824f)
#define TColorPaleGreen           ColorF (0.560784f, 0.737255f, 0.560784f)
#define TColorPink                ColorF (0.737255f, 0.560784f, 0.560784f)
#define TColorPlum                ColorF (0.917647f, 0.678431f, 0.917647f)
#define TColorRed                 ColorF (1.0f, 0.0f, 0.0f)
#define TColorSalmon              ColorF (0.435294f, 0.258824f, 0.258824f)
#define TColorSeaGreen            ColorF (0.137255f, 0.556863f, 0.419608f)
#define TColorSienna              ColorF (0.556863f, 0.419608f, 0.137255f)
#define TColorSkyBlue             ColorF (0.196078f, 0.6f, 0.8f)
#define TColorSlateBlue           ColorF (0.0f, 0.498039f, 1.0f)
#define TColorSpringGreen         ColorF (0.0f, 1.0f, 0.498039f)
#define TColorSteelBlue           ColorF (0.137255f, 0.419608f, 0.556863f)
#define TColorTan                 ColorF (0.858824f, 0.576471f, 0.439216f)
#define TColorThistle             ColorF (0.847059f, 0.74902f, 0.847059f)
#define TColorTransparent         ColorF (0.0f, 0.0f, 0.0f, 0.0f)
#define TColorTurquoise           ColorF (0.678431f, 0.917647f, 0.917647f)
#define TColorViolet              ColorF (0.309804f, 0.184314f, 0.309804f)
#define TColorVioletRed           ColorF (0.8f, 0.196078f, 0.6f)
#define TColorWheat               ColorF (0.847059f, 0.847059f, 0.74902f)
#define TColorYellow              ColorF (1.0f, 1.0f, 0.0f)
#define TColorYellowGreen         ColorF (0.6f, 0.8f, 0.196078f)
