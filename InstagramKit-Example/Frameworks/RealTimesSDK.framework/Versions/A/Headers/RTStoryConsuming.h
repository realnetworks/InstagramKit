//
//  StoryConsumer.h
//  RealTimesSDK
//
//  Created by Ante Trbojevic 1 on 10/06/15.
//  Copyright (c) 2015 RealNetworks. All rights reserved.
//

#import <Foundation/Foundation.h>

@class RTStory;
@class RTStoryBuilder;

/** The story consumer is used by the story builder as a sink to which it passes newly created story objects. 
 The consumer can then either keep the story object around in RAM or it may store the story object to a persistent data store for latter retrieval.
 
 See RTStoryBuilder for more information.
 */
@protocol RTStoryConsuming <NSObject>


/** @name Methods */

/** Invoked by the story builder when a new story has been created. 
 
 @param builder The story builder.
 @param story The story.
 */
- (void)storyBuilder:(RTStoryBuilder *)builder didCreateStory:(RTStory *)story;

/** Called when the creation of stories has started.
 
 @param builder The story builder.
 */
- (void)storyBuilderDidStartStoryCreation:(RTStoryBuilder *)builder;

/** Called when the creation of stories has completed.
 
 @param builder The story builder.
 */
- (void)storyBuilderDidCompleteStoryCreation:(RTStoryBuilder *)builder;

@end
