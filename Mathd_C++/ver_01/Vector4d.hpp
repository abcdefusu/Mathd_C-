//
//  Vector4d.hpp
//  XYZ
//  Vector4d������ģ��C++ʵ�֡���װ�˳��ó�Ա�뷽����
//
//  Created by yangbo on 24-08-08.
#ifndef VECTOR4D_H
#define VECTOR4D_H

#include <cmath>
#include <stdexcept>
#include <sstream>
#include <iomanip> 
#include "math_utils.hpp"
namespace XYZ {
    template <typename T>
    class Vector4d {
    public:
        T x, y, z, w;
        // ��̬����
        static const Vector4d<T> zero;
        static const Vector4d<T> one;
		// ���캯��
		Vector4d(T x = T(0), T y = T(0), T z = T(0), T w = T(0)) : x(x), y(y), z(z), w(w) {}
        // ��������
        ~Vector4d() {};
		// ������
        T& operator[](int index) {
            switch (index) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
            default: throw std::out_of_range("Invalid Vector4d index!");
            }
        }
        const T& operator[](int index) const {
            switch (index) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
            default: throw std::out_of_range("Invalid Vector4d index!");
            }
        }
    // ����������
    public:
        // ��ֵ������
        Vector4d<T>& operator=(const Vector4d<T>& v) {
            if (this != &v) {
				x = v.x; y = v.y; z = v.z; w = v.w;
            }
            return *this;
        }
        Vector4d<T>& operator+=(const Vector4d<T>& v) {
			x += v.x; y += v.y; z += v.z; w += v.w;
            return *this;
        }
        Vector4d<T>& operator-=(const Vector4d<T>& v) {
			x -= v.x; y -= v.y; z -= v.z; w -= v.w;
            return *this;
        }
        Vector4d<T>& operator*=(T s) {
			x *= s; y *= s; z *= s; w *= s;
            return *this;
        }
        Vector4d<T>& operator/=(T s) {
            s = T(1) / s;
            x *= s;
            y *= s;
            z *= s;
			w *= s;
            return *this;
        }
        // ��ͨ
        friend Vector4d<T> operator+(const Vector4d<T>& a, const Vector4d<T>& b) {
            return Vector4d<T>(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
        }

        friend Vector4d<T> operator-(const Vector4d<T>& a) {
            return Vector4d<T>(-a.x, -a.y, -a.z, -a.w);
        }

        friend Vector4d<T> operator-(const Vector4d<T>& a, const Vector4d<T>& b) {
            return Vector4d<T>(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
        }

        friend Vector4d<T> operator*(T d, const Vector4d<T>& a) {
            return Vector4d<T>(a.x * d, a.y * d, a.z * d, a.w * d);
        }

        friend Vector4d<T> operator*(const Vector4d<T>& a, T d) {
            return Vector4d<T>(a.x * d, a.y * d, a.z * d, a.w * d);
        }

        friend Vector4d<T> operator/(const Vector4d<T>& a, T d) {
            return Vector4d<T>(a.x / d, a.y / d, a.z / d, a.w / d);
        }

        friend bool operator==(const Vector4d<T>& lhs, const Vector4d<T>& rhs) {
            return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
        }

        friend bool operator!=(const Vector4d<T>& lhs, const Vector4d<T>& rhs) {
            return !(lhs == rhs);
        }
		// ����ת��
        operator Vector2d<T>() const { return Vector2d<T>{x, y};}
        operator Vector3d<T>() const { return Vector3d<T>{x, y, z}; }
	public:
        // ��ֵ ���޸Ķ����ڲ�״̬��
        void Set(T new_x = 0, T new_y = 0, T new_z = 0) {
            x = new_x;
            y = new_y;
            z = new_z;
        }
        // ��һ�����޸Ķ����ڲ�״̬��
        void Normalize() {
            T len = sqrt(SqrMagnitude());
            if (len > sTolerance)
            {
                x /= len;
                y /= len;
                z /= len;
                w /= len;
            }
        }
        // ģ��
        T Magnitude() const {
            return sqrt(x * x + y * y + z * z + w * w);
        }
        // ģ��ƽ��
        T SqrMagnitude() const {
            return x * x + y * y + z * z + w * w;
        }
        // ����
        void Scale(const Vector4d<T>& scale) {
            x *= scale.x;
            y *= scale.y;
            z *= scale.z;
            w *= scale.w;
        }
        // ���
        T Dot(const Vector4d<T>& vec) const {
            return vec.x * x + vec.y * y + vec.z * z + vec.w * w;
        }
        // ����
        T Distance(const Vector4d<T>& vec) const {
            return sqrt((x - vec.x) * (x - vec.x) + (y - vec.y) * (y - vec.y) + (z - vec.z) * (z - vec.z) + (w - vec.w) * (w - vec.w));
        }
        // ��ʽ���ַ���
        std::string ToString() {
            std::stringstream ss;
            ss << "(" << x << ", " << y << ", " << z << ", " << w << ")";
            return ss.str();
        }
        // ��ϣֵ
        size_t GetHashCode() {
            size_t hash = 17;
            hash = hash * 31 + std::hash<double>{}(x);
            hash = hash * 31 + std::hash<double>{}(y);
            hash = hash * 31 + std::hash<double>{}(z);
            hash = hash * 31 + std::hash<double>{}(w);
            return hash;
        }
        // �ж��Ƿ����
        bool Equals(const Vector4d<T>& other) {
            return this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w;
        }
        // ��ʽ���ַ���
        std::string ToString(const std::string& format) {
            std::stringstream ss;
            ss << "(";
            if (format == "F1") {
                ss << std::fixed << std::setprecision(1) << x << ", " << y << ", " << z << ", " << w;
            }
            else if (format == "F2") {
                ss << std::fixed << std::setprecision(2) << x << ", " << y << ", " << z << ", " << w;
            }
            else if (format == "F3") {
                ss << std::fixed << std::setprecision(3) << x << ", " << y << ", " << z << ", " << w;
            }
            ss << ")";
            return ss.str();
        }
    // ��̬��������
    public:
        // ��һ��
        static inline Vector4d<T> Normalize(const Vector4d<T>& vec) {
            T len = vec.SqrMagnitude();
            if (len > sTolerance) {
                len = sqrt(len);
                return Vector4d<T>(vec.x / len, vec.y / len, vec.z / len, vec.w / len);
            }
            return vec;
        }
        // ģ��
        static inline T Magnitude(const Vector4d<T>& vec) {
            return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
        }
        // ģ��ƽ��
        static inline T SqrMagnitude(const Vector4d<T>& v) {
            return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
        }
        // ���
        static inline T Dot(const Vector4d<T>& vec1, const Vector4d<T>& vec2) {
            return T(vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w);
        }
        // ����
        static inline T Distance(const Vector4d<T>& vec1, const Vector4d<T>& vec2) {
            return sqrt((vec1.x - vec2.x) * (vec1.x - vec2.x) + (vec1.y - vec2.y) * (vec1.y - vec2.y) + (vec1.z - vec2.z) * (vec1.z - vec2.z) + (vec1.w - vec2.w) * (vec1.w - vec2.w));
        }
        // ���Բ�ֵ
        static inline Vector4d<T> Lerp(const Vector4d<T>& a, const Vector4d<T>& b, const T& t) {
            if (t <= sTolerance) {
                return a;
            }
            else if (t >= 1 - sTolerance) {
                return b;
            }
            return a + (b - a) * t;
        }
        // ���Բ�ֵ�������ƣ�
        static inline Vector4d<T> LerpUnclamped(const Vector4d<T>& a, const Vector4d<T>& b, const T& t) {
            return a + (b - a) * t;
        }
        // ���ֵ��X,Y,Z��ȡ���
        static inline Vector4d<T> Max(const Vector4d<T>& lhs, const Vector4d<T>& rhs) {
            Vector4d<T> temp;
            temp.x = std::max(lhs.x, rhs.x);
            temp.y = std::max(lhs.y, rhs.y);
            temp.z = std::max(lhs.z, rhs.z);
            temp.w = std::max(lhs.w, rhs.w);
            return temp;
        }
        // ��Сֵ��X,Y,Z��ȡ��С��
        static inline Vector4d<T> Min(const Vector4d<T>& lhs, const Vector4d<T>& rhs) {
            Vector4d<T> temp;
            temp.x = std::min(lhs.x, rhs.x);
            temp.y = std::min(lhs.y, rhs.y);
            temp.z = std::min(lhs.z, rhs.z);
            temp.w = std::min(lhs.w, rhs.w);
            return temp;
        }
        // ��Ŀ����ƶ�
        static inline Vector4d<T> MoveTowards(const Vector4d<T>& current, const Vector4d<T>& target, const T& maxDistanceDelta) {
            Vector4d<T> a = target - current;
            T magnitude = a.Magnitude();
            if (magnitude <= maxDistanceDelta || magnitude < sTolerance)
            {
                return target;
            }
            return current + a / magnitude * maxDistanceDelta;
        }
        // ����ͶӰ
        static inline Vector4d<T> Project(const Vector4d<T>& vector, const Vector4d<T>& onNormal) {
            if (vector == zero || onNormal == zero) {
                return zero;
            }
            return Dot(vector, onNormal) / (onNormal.Magnitude() * onNormal.Magnitude()) * onNormal;
           
        }
        // ��������
        static inline Vector4d<T> Scale(const Vector4d<T>& a, const Vector4d<T>& b) {
            return Vector4d<T>(a.x * b.x, a.y * b.y, a.z * b.z);
        }
    };
    template <typename T>
    const Vector4d<T> Vector4d<T>::zero{ 0, 0, 0 ,0 };

    template <typename T>
    const Vector4d<T> Vector4d<T>::one{ 1, 1, 1 ,1 };
    
} // namespace XYZW

#endif // VECTOR4D_H




