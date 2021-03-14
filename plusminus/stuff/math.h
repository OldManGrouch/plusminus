namespace Math {
#define M_PI 3.14159265358979323846f
#define M_RADPI	57.295779513082f
#define M_PI_F ((float)(M_PI))
#define RAD2DEG(x) ((float)(x) * (float)(180.f / M_PI_F))
#define DEG2RAD(x) ((float)(x) * (float)(M_PI_F / 180.f))
#define pow(n) (n)*(n)
	static volatile const double Tiny = 0x1p-1022;
	static volatile const double Infinity = INFINITY;
	typedef struct { double d0, d1; } double2;
	float sqrtn(const float& x) {
		union {
			int i;
			float x;
		} u;
		u.x = x;
		u.i = (1 << 29) + (u.i >> 1) - (1 << 22);
		u.x = u.x + x / u.x;
		u.x = 0.25f * u.x + x / u.x;
		return u.x;
	}
	static inline double2 Mul112(double a, double b) {
		static const double c = 0x1p27 + 1;
		double
			ap = a * c, bp = b * c,
			a0 = (a - ap) + ap, b0 = (b - bp) + bp,
			a1 = a - a0, b1 = b - b0,
			d0 = a * b,
			d1 = a0 * b0 - d0 + a0 * b1 + a1 * b0 + a1 * b1;
		return double2{ d0, d1 };
	}
	static inline double2 Mul222(double2 a, double2 b) {
		static const double c = 0x1p27 + 1;
		double
			ap = a.d0 * c, bp = b.d0 * c,
			a0 = (a.d0 - ap) + ap, b0 = (b.d0 - bp) + bp,
			a1 = a.d0 - a0, b1 = b.d0 - b0,
			m0 = a.d0 * b.d0,
			m1 = a0 * b0 - m0 + a0 * b1 + a1 * b0 + a1 * b1 + (a.d0 * b.d1 + a.d1 * b.d0),
			d0 = m0 + m1,
			d1 = m0 - d0 + m1;
		return double2{ d0, d1 };
	}
	static inline double Mul121Special(double a, double2 b) {
		static const double c = 0x1p27 + 1;

		double
			ap = a * c, bp = b.d0 * c,
			a0 = (a - ap) + ap, b0 = (b.d0 - bp) + bp,
			a1 = a - a0, b1 = b.d0 - b0,
			m1 = a0 * b0 - 1 + a0 * b1 + a1 * b0 + a1 * b1 + a * b.d1;
		return m1;
	}
	static inline double2 Add212RightSmaller(double2 a, double b) {
		double
			c0 = a.d0 + b,
			c1 = a.d0 - c0 + b + a.d1,
			d0 = c0 + c1,
			d1 = c0 - d0 + c1;
		return double2{ d0, d1 };
	}
	static inline double Add221RightSmaller(double2 a, double2 b) {
		double
			c0 = a.d0 + b.d0,
			c1 = a.d0 - c0 + b.d0 + b.d1 + a.d1,
			d0 = c0 + c1;
		return d0;
	}
	float BOG_TO_GRD(float BOG) {
		return (180 / M_PI) * BOG;
	}

	float GRD_TO_BOG(float GRD) {
		return (M_PI / 180) * GRD;
	}
	static double Tail(double x) {
		if (1 <= x) return 1 == x ? 0x3.243f6a8885a308d313198a2e03707344ap-1 + Tiny : Infinity - Infinity;
		static const double p01 = 0.2145993335526539017488949;
		static const double p02 = -0.0890259194305537131666744;
		static const double p03 = 0.0506659694457588602631748;
		static const double p04 = -0.0331919619444009606270380;
		static const double p05 = 0.0229883479552557203133368;
		static const double p06 = -0.0156746038587246716524035;
		static const double p07 = 0.0097868293573384001221447;
		static const double p08 = -0.0052049731575223952626203;
		static const double p09 = 0.0021912255981979442677477;
		static const double p10 = -0.0006702485124770180942917;
		static const double p11 = 0.0001307564187657962919394;
		static const double p12 = -0.0000121189820098929624806;
		double polynomial = ((((((((((((
			+ p12) * x
			+ p11) * x
			+ p10) * x
			+ p09) * x
			+ p08) * x
			+ p07) * x
			+ p06) * x
			+ p05) * x
			+ p04) * x
			+ p03) * x
			+ p02) * x
			+ p01) * x;
		static const double2
			HalfPi = { 0x1.921fb54442d18p+0, 0x1.1a62633145c07p-54 },
			p00 = { -0x1.921fb31e97d96p0, +0x1.eab77149ad27cp-54 };
		double e = 1 / sqrt(1 - x);
		double2 ex = Mul112(e, 1 - x);
		double e2x = Mul121Special(e, ex);
		double2 t0 = Add212RightSmaller(ex, ex.d0 * -.5 * e2x);
		return Add221RightSmaller(HalfPi, Mul222(t0, Add212RightSmaller(p00, polynomial)));
	}
	float abs(float a) {
		if (a < 0.f) return -a;
		else return a;
	}
	float asin(float x) {
		float negate = float(x < 0);
		x = abs(x);
		float ret = -0.0187293;
		ret *= x;
		ret += 0.0742610;
		ret *= x;
		ret -= 0.2121144;
		ret *= x;
		ret += 1.5707288;
		ret = 3.14159265358979 * 0.5 - sqrt(1.0 - x) * ret;
		return ret - 2 * negate * ret;
	}
	__forceinline float Dot(const Vector3& Vec1, const Vector3& Vec2) {
		return Vec1[0] * Vec2[0] + Vec1[1] * Vec2[1] + Vec1[2] * Vec2[2];
	}
	__forceinline float Distance_3D(const Vector3& Src, const Vector3& Dst) {
		return sqrtf(pow((Src.x - Dst.x), 2) + pow((Src.y - Dst.y), 2) + pow((Src.z - Dst.z), 2));
	}
	__forceinline float Distance_2D(const Vector2& Src, const Vector2& Dst) {
		return sqrt(powf(Src.x - Dst.x, 2) + powf(Src.y - Dst.y, 2));
	}
	float NormalizeAngle(float angle) {
		while (angle > 360.0f) {
			angle -= 360.0f;
		}
		while (angle < 0.0f) {
			angle += 360.0f;
		}
		return angle;
	}
	Vector3 NormalizeAngles(Vector3 angles) {
		angles.x = NormalizeAngle(angles.x);
		angles.y = NormalizeAngle(angles.y);
		angles.z = NormalizeAngle(angles.z);
		return angles;
	}
	Vector3 EulerAngles(Quaternion q1) {
		float num = q1.w * q1.w;
		float num2 = q1.x * q1.x;
		float num3 = q1.y * q1.y;
		float num4 = q1.z * q1.z;
		float num5 = num2 + num3 + num4 + num;
		float num6 = q1.x * q1.w - q1.y * q1.z;
		Vector3 vector;
		if (num6 > 0.4995f * num5) {
			vector.y = 2.0f * std::atan2f(q1.y, q1.x);
			vector.x = 1.57079637f;
			vector.z = 0.0f;
			return NormalizeAngles(vector * 57.2958f);
		}
		if (num6 < -0.4995f * num5) {
			vector.y = -2.0f * std::atan2f(q1.y, q1.x);
			vector.x = -1.57079637f;
			vector.z = 0.0f;
			return NormalizeAngles(vector * 57.2958f);
		}
		Quaternion quaternion = Quaternion(q1.w, q1.z, q1.x, q1.y);
		vector.y = std::atan2f(2.0f * quaternion.x * quaternion.w + 2.0f * quaternion.y * quaternion.z, 1.0f - 2.0f * (quaternion.z * quaternion.z + quaternion.w * quaternion.w));
		vector.x = std::asin(2.0f * (quaternion.x * quaternion.z - quaternion.w * quaternion.y));
		vector.z = std::atan2f(2.0f * quaternion.x * quaternion.y + 2.0f * quaternion.z * quaternion.w, 1.0f - 2.0f * (quaternion.y * quaternion.y + quaternion.z * quaternion.z));
		return NormalizeAngles(vector * 57.2958f);
	}
	
	Vector3 RotatePoint(Vector3 center, Vector3 origin, float angle) {
		float num = angle * 0.0174532924f;
		float num2 = -std::sin(num);
		float num3 = std::cos(num);
		origin.x -= center.x;
		origin.z -= center.z;
		float num4 = origin.x * num3 - origin.z * num2;
		float num5 = origin.x * num2 + origin.z * num3;
		float num6 = num4 + center.x;
		num5 += center.z;
		return Vector3(num6, origin.y, num5);
	}
	__forceinline Vector2 CalcAngle(const Vector3& Src, const Vector3& Dst) {
		Vector3 dir = Src - Dst;
		return Vector2{ RAD2DEG(asin(dir.y / dir.Length())), RAD2DEG(-atan2(dir.x, -dir.z)) };
	}
	__forceinline Vector3 CalcAngle3D(const Vector3& Src, const Vector3& Dst) {

		Vector3 Delta = Src - Dst, AimAngles;

		float Hyp = sqrtf(powf(Delta.x, 2.f) + powf(Delta.y, 2.f));

		AimAngles.y = atanf(Delta.y / Delta.x) * M_RADPI;

		AimAngles.x = atanf(Delta.z / Hyp) * M_RADPI;

		if (Delta.x >= 0.f) AimAngles.y += 180.f;

		AimAngles.z = 0.f; return AimAngles;

	}
}
namespace NotVector3 {
	Vector3 Lerp(Vector3 a, Vector3 b, float t) {
		return a + (b - a) * t;
	}
}