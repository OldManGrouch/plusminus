class Vector3 {
public:
	float x, y, z;

	Vector3() { x = y = z = 0.0f; }
	Vector3(float X, float Y, float Z) { x = X; y = Y; z = Z; }
	float operator[](int i) const { return ((float*)this)[i]; }
	Vector3& operator-=(float v) { x -= v; y -= v; z -= v; return *this; }
	Vector3 operator*(float v) const { return Vector3(x * v, y * v, z * v); }
	Vector3 operator/(float v) const { return Vector3(x / v, y / v, z / v); }
	Vector3& operator+=(const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
	Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
	bool operator==(const Vector3& b) const { return x == b.x && y == b.y && z == b.z; }
	Vector3& operator-=(const Vector3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
	Vector3 operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
	inline float Length() { return sqrtf(x * x + y * y + z * z); }
	float Magnitude() { return sqrt(this->x * this->x + this->y * this->y + this->z * this->z); }
	Vector3 Normalized() { float num = this->Magnitude(); if (num > 9.99999974737875E-06) { return { this->x / num, this->y / num, this->z / num }; } return Vector3(); }
	float Distance(Vector3 b) { Vector3 calc(this->x - b.x, this->y - b.y, this->z - b.z); return sqrt(calc.x * calc.x + calc.y * calc.y + calc.z * calc.z); }
	Vector3 midPoint(Vector3 v2) { return Vector3((x + v2.x) / 2, (y + v2.y) / 2, (z + v2.z) / 2); }
};
template<typename T>
class list {
public:
	T get(uint32_t idx) {
		const auto internal_list = reinterpret_cast<uintptr_t>(this + 0x20);
		return *reinterpret_cast<T*>(internal_list + idx * sizeof(T));
	}

	T get_value(uint32_t idx) {
		const auto list = *reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x10);
		const auto internal_list = list + 0x20;
		return *reinterpret_cast<T*>(internal_list + idx * sizeof(T));
	}

	T operator[](uint32_t idx) { return get(idx); }

	const uint32_t get_size() { return *reinterpret_cast<uint32_t*>((uintptr_t)this + 0x18); }

	template<typename F>
	void for_each(const F callback) {
		for (auto i = 0; i < get_size(); i++) {
			auto object = this->get(i);
			if (!object)
				continue;
			callback(object, i);
		}
	}
};

class Vector2 {
public:
	float x, y;

	inline Vector2() { x = y = 0.0f; }
	inline Vector2 operator/(float v) const { return Vector2(x / v, y / v); }
	inline Vector2& operator/=(int v) { x /= v; y /= v; return *this; }
	inline Vector2(float X, float Y) { x = X; y = Y; }
	inline Vector2 operator-(const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
	inline Vector2 operator+(const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
	inline Vector2& operator+=(const Vector2& v) { x += v.x; y += v.y; return *this; }
	inline Vector2& operator-=(const Vector2& v) { x -= v.x; y -= v.y; return *this; }
	inline bool Zero() const { return (x > -0.1f && x < 0.1f && y > -0.1f && y < 0.1f); }
	inline Vector2 Clamp() {
		if (x > 180)
			x -= 360;
		else if (x < -180)
			x += 360;

		if (y > 180)
			y -= 360;
		else if (y < -180)
			y += 360;

		if (x < -89)
			x = -89;

		if (x > 89)
			x = 89;

		while (y < -180.0f)
			y += 360.0f;

		while (y > 180.0f)
			y -= 360.0f;

		return *this;
	}
};
class Vector4 {
public:
	float x, y, z, w;
	inline Vector4() { x = y = z = w = 0.0f; }
	inline Vector4(float X, float Y, float Z, float W) { x = X; y = Y; z = Z; w = W; }
};
class Rect {
public:
	float x; // 0x10
	float y; // 0x14
	float wid; // 0x18
	float hei; // 0x1C
	Rect(float x, float y/*top left*/, float x_rightsize, float y_downsize) { this->x = x; this->y = y; wid = x_rightsize; hei = y_downsize; }
	Rect() { this->x = 0; this->y = 0; wid = 0; hei = 0; }
	bool Contains(Vector2 point) { return point.x >= x && point.x < (x + wid) && point.y >= y && point.y < (y + hei); }
};
class Color {
public:
	float r;
	float g;
	float b;
	float a;
	Color(float rr, float gg, float bb, float aa) {
		r = rr;
		g = gg;
		b = bb;
		a = aa;
	}
};
struct Ray {
	Vector3 origin;
	Vector3 dir;
	Ray(Vector3 o, Vector3 d) {
		origin = o;
		dir = d;
	}
	Ray() {}
};


struct Matrix4x4 {
	union {
		struct {
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;

		}; float m[4][4];
	};
};
enum class EventType : int {
	MouseDown = 0,
	MouseUp = 1,
	MouseDrag = 3,
	KeyDown = 4,
	KeyUp = 5,
	Repaint = 7
};
enum class ButtonS : int {
	FORWARD = 2,
	BACKWARD = 4,
	LEFT = 8,
	RIGHT = 16,
	JUMP = 32,
	DUCK = 64,
	SPRINT = 128,
	USE = 256,
	FIRE_PRIMARY = 1024,
	FIRE_SECONDARY = 2048,
	RELOAD = 8192,
	FIRE_THIRD = 134217728
};
#define MAX_STRING_LEN 64
class Str {
	char zpad[0x10];
public:
	int size;
	wchar_t str[MAX_STRING_LEN + 1];
	Str(const wchar_t* st) {
		size = min(m_wcslen((wchar_t*)st), MAX_STRING_LEN);
		for (int i = 0; i < size; i++) {
			str[i] = st[i];
		}
		str[size] = 0;
	}
};
struct TreeMarkerDataMarkerLocation {
	Vector3 LocalPosition;
	Vector3 LocalNormal;
};
