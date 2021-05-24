#ifndef POINT_HPP
#define POINT_HPP

namespace Engine {
    /// @brief Can be used as 2D coordinate point or 2D vector.
    struct Point {
        // The coordinates of the point.
        float x, y;
        /// @brief Construct a Point with coordinate (0, 0).
        explicit Point();
        /// @brief Construct a Point with coordinate (x, y).
        /// @param x X coordinate of the point
        /// @param y Y coordinate of the point
        explicit Point(float x, float y);
        /// @brief Compare between Points.
        /// @return Determines whether the two Points have the same coordinate.
        bool operator==(const Point& rhs) const;
        /// @brief Compare between Points.
        /// @return Determines whether the two Points have distinct coordinate.
        bool operator!=(const Point& rhs) const;
        /// @brief Add points.
        /// @return The added result.
        Point operator+(const Point& rhs) const;
        /// @brief Subtract points.
        /// @return The subtracted result.
        Point operator-(const Point& rhs) const;
        /// @brief Multiply the point's coordinate with a scalar.
        /// @return The multiplied result.
        Point operator*(const float& rhs) const;
        /// @brief Divide the point's coordinate with a scalar.
        /// @return The divided result.
        Point operator/(const float& rhs) const;
        /// @brief Make point act like vector and get the normalized vector.
        /// @return The normalized vector.
        Point Normalize() const;
        /// @brief Make point act like vector and get the inner product.
        
        /// @param rhs The second vector.
        /// @return The inner product.
        float Dot(const Point& rhs) const;
        /// @brief Make point act like vector and get the squared magnitude.
        /// @return Squared magnitude of vector.
        float MagnitudeSquared() const;
        /// @brief Make point act like vector and get the magnitude.
        /// @return Magnitude of vector.
        float Magnitude() const;
    };
    Point operator*(const float& lhs, const Point& rhs);
}
#endif // POINT_HPP
