//
//  Location.h
//  RealTimesSDK
//
//  Created by Ante Trbojevic 1 on 09/06/15.
//  Copyright (c) 2015 RealNetworks. All rights reserved.
//

#import <Foundation/Foundation.h>

/*
 *  RTLocationDegrees
 *
 *  Discussion:
 *    Type used to represent a latitude or longitude coordinate in degrees under the WGS 84 reference
 *    frame. The degree can be positive (North and East) or negative (South and West).
 */
typedef double RTLocationDegrees;

/*
 *  RTLocationDistance
 *
 *  Discussion:
 *    Type used to represent a distance in meters.
 */
typedef double RTLocationDistance;

/** Represents a geographic location. A location consists of mandatory longitude and latitude information and optional textual information about the location (country, region, city and placename).
 
 The textual information is used by the story builder to automatically create a human-readable title for a story. The order in which the textual information is considered for the title is this:
 
 * use placename, if it is not *nil*
 
 * use city, if it is not *nil*
 
 * use region, if it is not *nil*
 
 * use country, if it is not *nil*

 */
@interface RTLocation : NSObject <NSSecureCoding, NSCopying>


/** @name Constructors */

/** Creates a location.
 
 Use this constructor if you do not have textual location information available at object creation time. You can set the textual information later by calling appropriate setter methods.
 
 @param longitude The longitude.
 @param latitude The latitude.
 */
- (id)initWithLongitude:(RTLocationDegrees)longitude latitude:(RTLocationDegrees)latitude;

/** Creates a location.
 
 @param longitude The longitude.
 @param latitude The latitude.
 @param country The country, *nil* if not available.
 @param region The region, *nil* if not available.
 @param city The city, *nil* if not available.
 @param placename The placename, *nil* if not available.
 */
- (id)initWithLongitude:(RTLocationDegrees)longitude
               latitude:(RTLocationDegrees)latitude
                country:(NSString *)country
                 region:(NSString *)region
                   city:(NSString *)city
              placename:(NSString *)placename;


/** @name Properties */

/** Gets the latitude linked to the location. */
@property (readonly, nonatomic) RTLocationDegrees latitude;

/** Gets the longitude linked to the location. */
@property (readonly, nonatomic) RTLocationDegrees longitude;

/** Gets the country linked to the location. */
@property (readonly, copy, nonatomic) NSString *country;

/** Gets  the region linked to the location. */
@property (readonly, copy, nonatomic) NSString *region;

/** Gets the city linked to the location. */
@property (readonly, copy, nonatomic) NSString *city;

/** Gets  the placename linked to the location. */
@property (readonly, copy, nonatomic) NSString *placename;


/** @name Methods */

/** Computes if the longitude and latitude is within specific distance.
 
 @param longitude The longitude.
 @param latitude The latitude.
 @param distance The distance.
 @return _YES_ if it is inside the distance, otherwise _NO_
 */
- (BOOL)inRadiusWithLongitude:(RTLocationDegrees)longitude
                     latitude:(RTLocationDegrees)latitude
                     distance:(RTLocationDistance)distance;

/** Compares itself with the passed object. 
 
 If the given object has the same longitude and latitude then it is equal.
 
 @param object Object for comapring.
 @return __YES__ if it is equal, otherwise __NO__
 */
- (BOOL)isEqualToLocation:(RTLocation *)object;

/** Returns location's hash code.
 
 @return The hash code.
 */
- (NSInteger)hash;

@end
