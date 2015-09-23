//
//  Story.h
//  RealTimesSDK
//
//  Created by Ante Trbojevic 1 on 05/06/15.
//  Copyright (c) 2015 RealNetworks. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RTStoryType.h"

@class RTTheme;

/** A story is a collection of scenes, each of which contain exactly one media item, which are related by their creation date and geographic location. A media item represents a single photo or video.
 
 Stories are usually created with the help of a RTStoryBuilder. The story builder forms stories out of media items that are made available to it through a RTMediaItemProviding. A story may be alternatively created from pre-determined set of media items with the help of the initWithType:mediaItems:title: constructor.
 
 A story has a set of hero media items. Those are the "best" media items based on the curation results and those are the items from which the story player should select scenes for story playback. Note however that the actual set of items that are ultimately part of the story playback experience may be a subset of the hero items. This subset is initially determined by the story player based on the playback target duration of the story and it can be later changed by the user through the content selection dialog in the story player user interface. You can get the set of scenes that were actually part of the story playback by calling the selectedScenes property.
 
 A story also has a theme. The theme stores information about how the story will be presented to the user when it is played back. E.g. which music track should be played or what type of transitions should be used.
 
 A story supports two ways to determine which of items are heros and which are not:
 
 * __manual selection__: you explicitly choose which items should be heros
 
 * __automatic selection__: the story class uses a special algorithm to select the most suitable items (based on curation information) as heros.
 
 Automatic hero item selection is based on algorithms which try to select the best items from the stories' collection of items. Note that you should curate a story with the help of the [RTCurator curateWithStory:options:listener:] before you invoke the automatic hero selection API. However you may still call autoSelectHeroItemsWithMaxCount: before you have curated a story, but in this case the auto-select method will assume that all videos and photos are of average quality.
 
 Note that for a freshly created story all media items in the story are treated as hero items.
 
 There are different types of stories: an event story consists of items which are in close time and location proximity while a trip story consists of photos and videos that were taken along a route which starts at your location, extends to some other location and then returns back to your home location. A user defined story on the other hand is created from a set of items that were explicitly selected by the user.
 
 Stories do have a set of representative media items which are always a subset of the stories' full set of media items. The representative items can be used to decide which thumbnails to use to visually represent the story in the user interface. You can specify the amount of representative items that should be returned when you ask for the representative items.
 
 ***Preparing up a story for playback***
 
 Since every story is created by the [RTStoryBuilder](RTStoryBuilder.html) with a reasonable default configuration, you can play back a story as soon as you receive it from the stroy builder. A story created this way will not have any curation information associated with it and the default set of hero items includes all items in the story. While this will give you a story that will play back correctly in the RealTimes application, the quality of the story will likely not be what a user expects. Consequently you should curate a story and adjust the set of hero items before you play a story for the first very time.
 
 Curating a story is an optional step because it can be very processor and time intensive. You curate a story by calling the curate method [RTCurator curateWithStory:options:listener:]. The curation method takes among other things a a reference to a curation listener (see RTCurationListening) which is continuously informed about the curation progress. The result of the curation step is that the media items in the story are augmented with curation information which primarily consists of per-video and photo scores. The auto-hero-selection mechanism can then take advantage of these scores to choose the best videos and photos that should be included in the set of hero items.
 
 Once a story has been curated, you should select the most-desirable videos and photos by calling the autoSelectHeroItemsWithMaxCount: method on the story. You can specify the number of items that should be included into the set of hero items when you call this method. Alternatively you can set the hero selection to a specific set of items from the story by calling the heroItems property. Assigning this property makes sense in cases where the user should be able to explicitly configure the set of hero items or you have implemented your own hero item selection algorithm.
 */
@interface RTStory : NSObject <NSSecureCoding>


/** @name Constructors */

/** Constructs a story from a given set of media items.
 
 @param type The story type.
 @param items The items.
 @param title The story's title.
 @param titleIsDateBased __YES__ if title is date based.
 */
- (id)initWithType:(RTStoryType)type mediaItems:(NSArray *)items title:(NSString *)title titleIsDateBased:(BOOL)titleIsDateBased;


/** @name Properties */

/** Gets the story identifier.
 
 */
@property (readonly, copy, nonatomic) NSString *identifier;

/** Gets the type of the story.
 
 @return The story type.
 */
@property (readonly, nonatomic) RTStoryType storyType;

/** Returns the start date.
 This is the creation date of the oldest item in the story.
 
 @return The start date.
 */
@property (readonly, copy, nonatomic) NSDate *startDate;

/** Returns the end date.
 
 This is the creation date of the newest item in the story.
 
 @return The end date.
 */
@property (readonly, copy, nonatomic) NSDate *endDate;

/** Returns the story title.
 
 The title is automatically created by the story builder and it is based on the location of the items in the story and/or the story start and end dates.
 
 @return The title.
 */
@property (readonly, copy, nonatomic) NSString *title;

/** Returns the story title.
 
 Gets if title is date based title.
 
 @return Returns __YES__ if title is date based.
 */
@property (readonly, nonatomic) BOOL titleIsDateBased;

/** Gets the items in the stroy.
 
 This is the set of items for which the story was created. Note, however that only the actually selected items will be played back when you play a story.
 
 @return The items, each item is RTMediaItem.
 */
@property (readonly, copy, nonatomic) NSArray *mediaItems;

/** Allows you to manually select the media items that should be part of the story playback experience.
 
 The passed in items must be items that are part of the story.
 */
@property (copy, nonatomic) NSArray *heroItems;

/** Gets or sets the scenes which should be included in playback.
 
 Usually you should leave the selection to the story player, but you may call this method if you want to preserve an already existing selection from an older version of the story.
 
 Only scenes (RTScene objects) which are derived from items that are part of the story are added to the story. All other scenes are ignored.
 */
@property (copy, nonatomic) NSArray *selectedScenes;

/** The theme of the story.
 
 The story Theme contains information about how the story will be presented to the user. e.g. which music track to play or what transition types to use, etc.
 */
@property (copy, nonatomic) RTTheme *theme;


/** @name Methods */

/** Automatically selects media items based on the story's curation information.
 
 @param count The number of items to include into the selection.
 */
- (void)autoSelectHeroItemsWithMaxCount:(NSInteger)count;

/** Returns a collection of representative items.
 
 These are the items that are the best visual representation of the story and thus should be used to build story's thumbnail.
 
 @param count The number of desired representative items.
 @return The representative items of type RTMediaItem.
 */
- (NSArray *)representativeItemsWithMaxCount:(NSInteger)count;

@end
