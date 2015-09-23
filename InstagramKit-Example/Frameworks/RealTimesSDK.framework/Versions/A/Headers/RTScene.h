//
//  RTScene.h
//  RealTimesSDK
//
//  Created by Ante Trbojevic 1 on 15/06/15.
//  Copyright (c) 2015 RealNetworks. All rights reserved.
//

#import <Foundation/Foundation.h>

@class RTMediaItem;

/** An instance of a [RTScene](RTScene.html) describes a single scene in a story. A scene has a time range and a reference to the media item from which the scene was created.
 
 For video items the time range specifies the start time and duration of the section of the video that is played for this scene. For photos the time range is always (0, 0).
 */
@interface RTScene : NSObject


/** @name Constructors */

/** Creates a scene from the given RTMediaItem.
 
 @param item The media item.
 @param startTime The start time in seconds.
 @param duration The duration time in seconds.
 */
- (id)initWithMediaItem:(RTMediaItem *)item startTime:(NSTimeInterval)startTime duration:(NSTimeInterval)duration;


/** @name Properties */

/** Gets the media item. */
@property (readonly, nonatomic) RTMediaItem *mediaItem;

/** Gets the start time. */
@property (readonly, nonatomic) NSTimeInterval startTime;

/** Gets the duration. */
@property (readonly, nonatomic) NSTimeInterval duration;

/** Gets or sets if the scene is selected. */
@property (assign, nonatomic) BOOL isSelected;

@end
