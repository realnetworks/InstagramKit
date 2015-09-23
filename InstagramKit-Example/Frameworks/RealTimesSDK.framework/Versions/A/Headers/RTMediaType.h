//
//  MediaType.h
//  RealTimesSDK
//
//  Created by Ante Trbojevic 1 on 10/06/15.
//  Copyright (c) 2015 RealNetworks. All rights reserved.
//

/** A media type indicates what type of media an item represents.
 
 A media item may either represent a photo or a video.
 */
typedef NS_ENUM(NSInteger, RTMediaType){
    /** Photo type */
    RTMediaTypePhoto,
    
    /** Video type */
    RTMediaTypeVideo,
};