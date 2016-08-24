/**
 * Copyright (C) 2013-2016 The Gona Project
 *
 * Contact: airgiser@gmail.com
 */

#ifndef GONA_GEOGRAPHY_H
#define GONA_GEOGRAPHY_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdint.h>

/// the earth radius
#define EARTH_RADIUS 6378137

/** \struct GnLatLng
 *
 *  A pair of (lat,lon) geography coordinate.
 */
struct GnLatLng {
  double latitude;
  double longitude;

  GnLatLng(double lat, double lon) : latitude(lat), longitude(lon) {}

  /**
   *  Calculate the great-circle distance between two points(over the earth's surface).
   *
   *  @param from coordinate of the first point.
   *  @param to coordinate of the second point.
   *
   *  @return distance(in meters) between the given two points.
   */
  static double getDistance(const GnLatLng &from, const GnLatLng &to) {
    double fromLat = toRadians(from.latitude);
	double fromLon = toRadians(from.longitude);
	double toLat = toRadians(to.latitude);
	double toLon = toRadians(to.longitude);
    
    // equirectangular approximation
    // x = Δλ ⋅ cos φm
    // y = Δφ
    //          _______
    // d = R ⋅ √x² + y²
    double x = (toLon - fromLon) * cos((fromLat + toLat) / 2);
    double y = (toLat - fromLat);
    return sqrt(x*x + y*y) * EARTH_RADIUS;
  }

  /**
   *  Calculate the initial bearing from the start point to the end point.
   *
   *  @param from coordinate of the start point
   *  @param to coordinate of the end point
   *
   *  @return bearing(degrees) from the start point to the end point.
   */
  static double getBearing(const GnLatLng &from, const GnLatLng &to) {
    double fromLat = toRadians(from.latitude);
	double toLat = toRadians(to.latitude);
	double deltaLon = toRadians(to.longitude - from.longitude);

    // θ = atan2( sin Δλ ⋅ cos φ2 , cos φ1 ⋅ sin φ2 − sin φ1 ⋅ cos φ2 ⋅ cos Δλ )
    double y = sin(deltaLon) * cos(toLat);
    double x = cos(fromLat)*sin(toLat) - sin(fromLat)*cos(toLat)*cos(deltaLon);
    double theta = atan2(y, x);
    double degrees = toDegrees(theta);
    return fmod(degrees + 360, 360);
  }

  /**
   *  Given a start point, initial bearing, and distance, calculate the destination point.
   *
   *  @param from     the start point
   *  @param bearing  the initial bearing
   *  @param distance distance from the start point
   *
   *  @return the destination point along great-circle given distance and bearing from start point
   */
  static GnLatLng getDestination(const GnLatLng &from, double bearing, double distance) {
    double fromLat = toRadians(from.latitude);
	double fromLon = toRadians(from.longitude);
    double b = toRadians(bearing);
    
    // φ2 = asin( sin φ1 ⋅ cos δ + cos φ1 ⋅ sin δ ⋅ cos θ )
    // λ2 = λ1 + atan2( sin θ ⋅ sin δ ⋅ cos φ1, cos δ − sin φ1 ⋅ sin φ2 )
    double ddR = distance/EARTH_RADIUS;
    double destLat = asin(sin(fromLat)*cos(ddR) + cos(fromLat)*sin(ddR)*cos(b));
    double destLon = fromLon + atan2(sin(b)*sin(ddR)*cos(fromLat), cos(ddR)-sin(fromLat)*sin(destLat));
    return GnLatLng(toDegrees(destLat), toDegrees(destLon));
  }

  /**
   *  Convert degrees to radians
   */
  static double toRadians(double degrees) {
	  return degrees * M_PI / 180;
  }

  /**
   *  Convert radians to degrees
   */
  static double toDegrees(double radians) {
	  return radians * 180 / M_PI;
  }
};

#endif // GONA_GEOGRAPHY_H
