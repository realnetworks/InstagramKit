//
//  CurationInfo.h
//  RealTimesSDK
//
//  Created by Ante Trbojevic 1 on 09/06/15.
//  Copyright (c) 2015 RealNetworks. All rights reserved.
//

#import "RTVideoSegmentScore.h"


/** An instance of RTCurationInfo represents the curation information that was computed for a single media item.
 */
@interface RTCurationInfo : NSObject <NSSecureCoding, NSCopying>


/** @name Constructors */

/** Creates a curation info object with curation information for a photo.
 
 @param signature The signature (optional) as a base64 string.
 @param score The overall score.
 @param sharpness The sharpness score.
 @param facesScores The faces score.
 @param nonPersonalFlag Personal (___NO___) or non-personal (___YES___) media item based on meta-data.
 @param version The version of curation info.
 */
- (id)initWithSignature:(NSString *)signature score:(RTCurationScore)score sharpness:(RTCurationScore)sharpness facesScores:(RTCurationScore)facesScores nonPersonalFlag:(BOOL)nonPersonalFlag version:(NSString *)version;

/** Creates a curation info object with curation information for a video.
 
 @param score The overall score
 @param sceneEvents The scene events with scores (objects of RTVideoSegmentScore).
 @param nonPersonalFlag  Personal (___NO___) or non-personal (___YES___) media item based on meta-data.
 @param version The version of curation info.
 */
- (id)initWithScore:(RTCurationScore)score sceneEvents:(NSArray *)sceneEvents nonPersonalFlag:(BOOL)nonPersonalFlag version:(NSString *)version;


/** @name Properties */

/** Returns the signature as a base64 string.
 
 The signature allows you detect whether to photos are the same or different. Note that only photos have a signature. *Nil* is returned if the receiver does not represent the curation information of a photo.
 */
@property (readonly, copy, nonatomic) NSString *signature;

/** Returns the overall curation score of a media item.
 
 The score is in the range -1...0...1 where 0 represents a average quality item, a negative value represents an item of less quality than the average and a positive value represents an item of better than average quality.
 */
@property (readonly, nonatomic) RTCurationScore score;

/** Returns the sharpness score.
 
 The score is in the range 0...1 where a value of 0 represents a very blurred photo and a value of 1 a perfectly sharp photo.
 */
@property (readonly, nonatomic) RTCurationScore sharpness;

/** Returns the faces score.
 
 The faces score represents the probability of the existance of faces in the photo. Confidence level of face presence is in range [0, 1], but it can exceed value of 1.0. Value of 0.5 means 50% confidence in face presence.  Value of 1.0 means 100% confidence.  Value of 1.5 means 100% confidence but higher quality face photo than photo of faces score of 1.0.
 */
@property (readonly, nonatomic) RTCurationScore facesScore;

/** Returns top 10 per-scene scores.
 
  A video file is broken down by the curation mechanism into individual scenes and each scene is assigned a score in the range -1...0...1. A photo has only one scene score. Each item is RTVideoSegmentScore object.
 */
@property (readonly, copy, nonatomic) NSArray *sceneEvents;

/** The version of the curation info object.
 
 This can be used to determine version compatibility when storing/restoring instance of RTCurationInfo object.
 */
@property (readonly, nonatomic) NSString* version;

/** Personal (___NO___) or non-personal (___YES___) media item based on meta-data.
 
 Any items present in camera-roll will be marked as personal unless established they are screen-shots or that they were inserted by non-apple application.
 */
@property (readonly, nonatomic) BOOL nonPersonalFlag;
@end
