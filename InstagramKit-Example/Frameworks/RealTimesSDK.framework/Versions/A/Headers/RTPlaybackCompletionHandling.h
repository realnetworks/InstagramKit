//
//  PlaybackCompletionHandler.h
//  RealTimesSDK
//
//  Created by Ante Trbojevic 1 on 10/06/15.
//  Copyright (c) 2015 RealNetworks. All rights reserved.
//

#import <Foundation/Foundation.h>

@class RTStoryPlayer;
@class RTStory;
@class RTStoryPlayerResponse;

/** Invoked once the RealTimes application has handled control back to this app. */
@protocol RTPlaybackCompletionHandling <NSObject>


/** @name Methods */

/** Invoked once control has returned from the story player to the calling activity. 
 
 The callback receives the story object which was played back and the state of the story object has been updated with any changes that the user may have applied in the RealTimes editor. E.g. if the user changed the selected items in the RealTimes editor, then a call to [RTStory selectedScenes] will return the new selection. The response object contains additional information about saved stories and story files. See RTStoryPlayerResponse for more information. The 'error' parameter will be *nil* if no error was encountered and the appropriate exception object if an error was encountered.
 
 @param sender The story player.
 @param story The story with the updated state.
 @param isStoryModified __YES__ if user has changed the story during the playback, otherwise __NO__.
 @param response The player response.
 @param error If it is not *nil* it contains the error that was encountered.
 @return _YES_ if the job is successfully done, otherwise _NO_ (check error).
 */
- (void)storyPlayer:(RTStoryPlayer *)sender didFinishPlayback:(RTStory *)story storyModified:(BOOL)isStoryModified response:(RTStoryPlayerResponse *)response error:(NSError *)error;

@end
