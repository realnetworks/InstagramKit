//
//  CollectionMediaItemProvider.h
//  RealTimesSDK
//
//  Created by Ante Trbojevic 1 on 09/06/15.
//  Copyright (c) 2015 RealNetworks. All rights reserved.
//

#import "RTMediaItemProviding.h"

/** A concrete implementation of a story builder media item provider which wraps around a collection of media items.
 */
@interface RTCollectionMediaItemProvider : NSObject <RTMediaItemProviding>


/** @name Constructors */

/** Creates a media item provider which wraps the given collection of media items.
 
 @param items The media item collection.
 */
- (id)initWithItems:(NSArray *)items;

@end
