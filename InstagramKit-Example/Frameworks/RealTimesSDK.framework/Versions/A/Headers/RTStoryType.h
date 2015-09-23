//
//  StoryType.h
//  RealTimesSDK
//
//  Created by Ante Trbojevic 1 on 05/06/15.
//  Copyright (c) 2015 RealNetworks. All rights reserved.
//

/** An enumeration that defines a story type.
 */
typedef NS_ENUM(NSInteger, RTStoryType){
    /** The ad hoc type */
    RTStoryTypeAdHoc,
    
    /** The away event type */
    RTStoryTypeAwayEvent,
    
    /** The home event type */
    RTStoryTypeHomeEvent,
    
    /** The trip event type */
    RTStoryTypeTripEvent
};
