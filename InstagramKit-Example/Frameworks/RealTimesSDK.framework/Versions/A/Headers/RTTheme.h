//
//  Theme.h
//  RealTimesSDK
//
//  Created by Ante Trbojevic 1 on 09/06/15.
//  Copyright (c) 2015 RealNetworks. All rights reserved.
//

#import <Foundation/Foundation.h>

/** The theme stores settings which determine how a story will be presented to the user. E.g. it stores information about the type of transitions that should be applied to the video and photo segments or what background music track should be played with the story.
 
 You can migrate the theme of a story A to a another story B simply by getting the theme object from story A and setting it on story B. The next time you play story B, the new theme settings will be used by the story player.
 
 You can also persist a theme object by serializing it with an object stream. The serialized data can then be stored in a file or as a BLOB in a SQLite database. The theme object can then be regenerated at a later time by de-serializing the persisted bytes. After that the theme object may be assigned to any existing story object.
 
 Note that a theme does not provide any API at this time to access or manipulate the individual settings. You may only get theme objects from a story object and set it on the same or different story object.
 */
@interface RTTheme : NSObject <NSSecureCoding>

@end
