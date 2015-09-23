//
//  StoryBuilder.h
//  RealTimesSDK
//
//  Created by Ante Trbojevic 1 on 05/06/15.
//  Copyright (c) 2015 RealNetworks. All rights reserved.
//

#import <Foundation/Foundation.h>

@class RTLocation;
@protocol RTMediaItemProviding;
@protocol RTStoryConsuming;

/** A story builder instance is used to create story objects from an existing collection of media items.
 
 Each media item represnts a single photo ot video and it has a distinct identity.
 
 You typically create an instance of a story builder when your activity starts up and you hold on to this instance until your activity is destroyed. You connect your story builder instance to your media library with the help of an object which conforms to the RTMediaItemProviding interface. You then connect the story builder to your application with the help of an object which conforms to the RTStoryConsuming interface. The media item provider allows the story builder to enumerate the media items in your media library in order to create stories when you call createStories on the story builder. A new complete set of stories is created each time createStories is called and each new story is passed to the story consumer object. Note that the story builder does not support incremental building of stories.
 
 Use an instance of the RTCollectionMediaItemProvider if your media items are stored in a Cocoa collection. You do not have to create your own RTMediaItemProviding implementation in this case. If however your media items are stored in a SQLLite database or similar and you want to be able to incrementally access the data in your database, then you need to create your own implementation of the RTMediaItemProviding which gets a cursor from your SQLLite database, iterates over the cursor and creates media item objects from the data in the cursor as needed.
 
 It is your responsibility in any case to create a suitable instance of a RTMediaItemProviding and to set it on the story builder before you call createStories for the first time. Note that the item provider is expected to return the media items ordered by creation date from newest creation date down to the oldest creation date.
 
 The story builder class offers a set of configuration options which control how stories are created and how many stories should be created by a single createStories call. Any change you make to those settings will be applied to the next createStories call.
 */
@interface RTStoryBuilder : NSObject


/** @name Constructors */

/** Creates a story builder.
 */
- (id)init;


/** @name Properties */

/** Gets or sets whether the story builder uses the home location to compute trip stories. */
@property (assign, nonatomic) BOOL useHomeLocation;

/** Gets or sets the home location. */
@property (copy, nonatomic) RTLocation *homeLocation;

/** Gets or sets the maximum number of media items that a story is expected to contain. */
@property (assign, nonatomic) NSInteger maxMediaItemsPerStory;

/** Gets or sets the minimum number of media items that a story is expected to contain. */
@property (assign, nonatomic) NSInteger minMediaItemsPerStory;

/** Gets or sets the media item provider which provides the story builder with media items. */
@property (retain) id <RTMediaItemProviding> mediaItemProvider;

/** Gets or sets the story consumer. */
@property (retain) id <RTStoryConsuming> storyConsumer;


/** @name Methods */

/**
 Enumerates through all media items in the media item collection encapsulated by the media item provider and creates stories based on the story builders current settings.

 Each newly created story is then returned to the story consumer. An appropriate exception is thrown if the current story builder settings are inconsistent.
 */
- (void)createStories;

@end
