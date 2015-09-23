//
//  MediaItem.h
//  RealTimesSDK
//
//  Created by Ante Trbojevic 1 on 05/06/15.
//  Copyright (c) 2015 RealNetworks. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RTMediaType.h"

@class RTCurationInfo;
@class RTLocation;

/** An instance of a media item is used to represent photo or a video.
 
 Every media item instance has a distinctive identy which is represented by the item identifier. The item identifier may be any string as long as it is unique among the set of all media items which is maintained by your media library.
 
 A media item has an asset file which is the full-resolution photo or video file. The location of this file is given by a URL. A media item also has a thumbnail which is a low-resolution version of the photo or a still image of a video. This thumbnail can be used to visually represent the media item in the user interface and it may also be used in the curation process if the asset file is not accessible at curation time.
 
 Media items have a creation date and a location. The creation date is usually the date at which a photo was taken or a video was shot. However you may set the creation date to the last known modification date of the photo or video file if a "date taken" property is not available for the file and the file system on which the file is stored does not support a creation date metadata field. The location information is optional because the user has to explicitly consent to the inclusion of location information when he takea a photo or shoots a video with the device's camera app. However it is strongly suggested to include location information with media items in order to ensure that the story builder will be able to create stories by taking advantage of location information.
 
 A media item may also have a curation info object which stores information about a photo or video which can be used to automatically select the best items of a story. The curation info can be assigned to a media item when a media item is created by a media item provider, if the curation info is available at that time, or it can be assigned to a media item at a latter time.
 
 ***Creating media items***
 
 You are expected to create media items in your implementation of the RTMediaItemProviding. Create one media item per photo and video stored in your media library. You will typically create the item only at the time that the story builder is asking the item provider for the next item. See [RTMediaItemProviding newMediaItem]. The item must at a minimum include the media type, identifier, asset information and the creation date. Additionally, if item type is video, duration must be set.
 
 ***Enabling caching of curation information***
 
 You can implement local caching of curation information by iterating over the media items of a story and grabbing the curation info objects from the media items after you have called [RTStoryCurator curateWithStory:Options:Listener:] and the curate method has finished its work. The curation info objects can then be serialized into a file or a SQLLite database. To make it possible to correctly re-associate a curation info object with the media ite to which it belongs when you want to read the curation info objects back into RAM, you should store the curation info objects together with the media item identifiers.
 
 Your media item provider implementation can then use the media item identifier to look up the associated curation info object in your curation info cache after you have constructed the media item object. Them simply set the deserialized curation info object on the media item before you return it from the [RTMediaItemProviding newMediaItem] method.
 */
@interface RTMediaItem : NSObject <NSSecureCoding>

/** @name Constructors */

/** Creates a media item. 
 @param type The media type.
 @param identifier The identifier.
 */
- (id)initWithType:(RTMediaType)type identifier:(NSString *)identifier;


/** @name Properties */

/** Gets the identifier.
 */
@property (readonly, nonatomic) NSString *identifier;

/** Gets or sets the media type.
 */
@property (readonly, nonatomic) RTMediaType mediaType;

/** Gets or sets the URI of the asset.
 The asset is the actual video or high-resolution photo. A typical resolution for a photo asset is 1024 x 1024 pixels.
 
 Library Asset ID is used to refer to an asset in iOS asset library, it is based on meta-data available and it is passed to the RealTimes application.
 
 Identifiers in the asset library are not specific to the application and can be shared.
 The identifier can be passed consistently as a URL.  Thus, URL can either refer to item in Cloud or on the device.
 
 - E.g. [assets-library://asset/asset.MOV?id=D1B6760E-AB93-42B2-B97F-2095B6EF9533&ext=MOV](assets-library://asset/asset.MOV?id=D1B6760E-AB93-42B2-B97F-2095B6EF9533&ext=MOV)
 
 In URL above id is GUID that identifes the item in devices library: _D1B6760E-AB93-42B2-B97F-2095B6EF9533_. These identifiers can be leveraged with older __ALAssets__ as well as new Photos APIs.
 
 If you want to reference item from the Verizon Cloud then the form assign HTTP path to the reference.
 */
@property (copy, nonatomic) NSURL *assetURL;

/** Gets or sets the URL of the thumbnail.
 The thumbnail is always an image file and it has a lower resolution than the main asset file. A typical thumbnail resolution would be 256 x 256 pixels.
 */
@property (copy, nonatomic) NSURL *thumbnailURL;

/** Gets or sets the creation date.
 */
@property (copy, nonatomic) NSDate *creationDate;

/** Gets or sets the location.
 */
@property (copy, nonatomic) RTLocation *location;

/** Gets or sets the duration of the media item.
 
 The duration is measured in seconds. The duration of a photo is 0.
 */
@property (assign, nonatomic) NSTimeInterval duration;

/** Gets or sets the title.
 */
@property (copy, nonatomic) NSString *title;

/** Gets or sets the curation info.
 
 The curation information is used by a Story object to decide which media items should be considered the "best" items among the items in the story. *Nil* is returned if the item has no curation information.
 */
@property (copy, nonatomic) RTCurationInfo *curationInfo;


/** @name Methods */

/** Returns true if the given object is a media item with the same identifier than the receiver has. 
 
 @param object The comparing media item object.
 */
- (BOOL)isEqualToMediaItem:(RTMediaItem *)object;

/** Returns the receiver's hash code.
 
 @return The hash code.
 */
- (NSUInteger)hash;

@end
