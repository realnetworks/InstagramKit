//
//  RTVideoSceneEvent.h
//  RealTimesSDK
//
//  Created by Ante Trbojevic 1 on 03/07/15.
//  Copyright (c) 2015 RealNetworks. All rights reserved.
//

#import <Foundation/Foundation.h>

/*
 *  RTCurationScore
 *
 *  Discussion:
 *    Type used to represent curation score.
 */
typedef float RTCurationScore;

/** A segment in video file evaluated with the score.
 */
@interface RTVideoSegmentScore : NSObject


/** @name Constructors */

/** Constructs the RTVideoSegmentScore
 
 @param score The video event score.
 @param startTime The starting time of a segment in the video.
 @param duration The duration of a segment in the video.
 */
- (id)initWithScore:(RTCurationScore)score startTime:(NSTimeInterval)startTime duration:(NSTimeInterval)duration;


/** @name Properties */

/** A score of video event in the range -1...0...1. */
@property (readonly, nonatomic) RTCurationScore score;

/** Gets the start time of video segment in seconds */
@property (readonly, nonatomic) NSTimeInterval startTime;

/** Gets the duration of video segment in seconds */
@property (readonly, nonatomic) NSTimeInterval duration;

@end
