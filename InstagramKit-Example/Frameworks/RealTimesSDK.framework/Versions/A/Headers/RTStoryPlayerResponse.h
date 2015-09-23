//
//  StoryPlayerResponse.h
//  RealTimesSDK
//
//  Created by Ante Trbojevic 1 on 10/06/15.
//  Copyright (c) 2015 RealNetworks. All rights reserved.
//

#import <Foundation/Foundation.h>

/** A story player response object is passed to the RTPlaybackCompletionHandling when the completion handler is invoked at the end of playback.
 
 The response object contains a list of Uri objects for each story video file that was saved and for each story video file that was shared by the user. It also contains a list of story objects which represents the state of the story when the user selected the "Save Story" / "Create Album" button in the player UI.
 */
@interface RTStoryPlayerResponse : NSObject


/** @name Properties */

/** Gets the list of stories which should be used to create albums.
 
 Each object in NSArray is RTStory.
 
 Each RTStory object represents the state of the story at the time the user tapped on the "Create Album" button. The list is sorted in chronological order from the most recent created album to the least recent save-point. An empty list is returned if the user did not save the story.
 */
@property (readonly, copy, nonatomic) NSArray *createdAlbumStories;

/** Gets the list of saved stories.
 
 Each object in NSArray is RTStory.
 
 Each story object represents the state of the story at the time the user tapped on the "Save Story" button. The list is sorted in chronological order from the most recent save-point to the least recent save-point. An empty list is returned if the user did not save the story.
 */
@property (readonly, copy, nonatomic) NSArray *savedStories;

/** Gets the list of saved story video files.
 
 Each object is of RTMediaItem type.
 
 The video files are saved in the camera roll. The list is sorted from the most recently shared video to the least recently shared video. An empty array is returned if the user did not share a video file.
 */
@property (readonly, copy, nonatomic) NSArray *savedStoryVideoFiles;

@end
