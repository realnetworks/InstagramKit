//
//    Copyright (c) 2015 Shyam Bhat
//
//    Permission is hereby granted, free of charge, to any person obtaining a copy of
//    this software and associated documentation files (the "Software"), to deal in
//    the Software without restriction, including without limitation the rights to
//    use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
//    the Software, and to permit persons to whom the Software is furnished to do so,
//    subject to the following conditions:
//
//    The above copyright notice and this permission notice shall be included in all
//    copies or substantial portions of the Software.
//
//    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
//    FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
//    COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
//    IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//    CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


#import "IKCollectionViewController.h"
#import "InstagramKit.h"
#import "IKCell.h"
#import "InstagramMedia.h"
#import "IKMediaViewController.h"
#import "IKLoginViewController.h"

#import <RealTimesSDK/RealTimesSDK.h>


#define kNumberOfCellsInARow 3
#define kFetchItemsCount 15

@interface IKCollectionViewController () <RTPlaybackCompletionHandling>

@property (nonatomic, strong)   NSMutableArray *mediaArray;
@property (nonatomic, strong)   InstagramPaginationInfo *currentPaginationInfo;
@property (nonatomic, weak)     InstagramEngine *instagramEngine;
@property (weak, nonatomic) IBOutlet UITextField *input;

@end


@implementation IKCollectionViewController

static NSString* API_KEY = @"3a25374f57c6aaf425908ee6a27949579c370e518f3045413a098cd9";


- (void)viewDidLoad
{
    [super viewDidLoad];

    self.mediaArray = [[NSMutableArray alloc] init];
    self.instagramEngine = [InstagramEngine sharedEngine];
    [self updateCollectionViewLayout];
    
    [self loadMedia];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(userAuthenticationChanged:)
                                                 name:InstagramKitUserAuthenticationChangedNotification
                                               object:nil];
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    [self.input resignFirstResponder];
}

/**
 *  Depending on whether the Instagram session is authenticated,
 *  this method loads either the publicly accessible popular media
 *  or the authenticated user's feed.
 */
- (void)loadMedia
{
    self.currentPaginationInfo = nil;
    
    BOOL isSessionValid = [self.instagramEngine isSessionValid];
    [self setTitle: (isSessionValid) ? @"My Feed" : @"Popular Media"];
    [self.navigationItem.leftBarButtonItem setTitle: (isSessionValid) ? @"Log out" : @"Log in"];
//    [self.navigationItem.rightBarButtonItem setEnabled: isSessionValid];
    [self.mediaArray removeAllObjects];
    [self.collectionView reloadData];
    
    if (isSessionValid) {
        [self requestSelfFeed];
    }
    else
    {
        [self requestPopularMedia];
    }
}


#pragma mark - API Requests -

/**
    Calls InstagramKit's helper method to fetch Popular Instagram Media.
 */
- (void)requestPopularMedia
{
    [self.instagramEngine getPopularMediaWithSuccess:^(NSArray *media, InstagramPaginationInfo *paginationInfo)
                                                        {
                                                            [self.mediaArray addObjectsFromArray:media];
                                                            [self.collectionView reloadData];
                                                        }
                                                       failure:^(NSError *error, NSInteger statusCode) {
                                                            NSLog(@"Load Popular Media Failed");
                                                       }];
}


/**
    Calls InstagramKit's helper method to fetch Media in the authenticated user's feed.
    @discussion The self.currentPaginationInfo object is updated on each successful call
    and it's updated nextMaxId is passed as a parameter to the next paginated request.
 */
- (void)requestSelfFeed
{
    [self.instagramEngine getSelfFeedWithCount:kFetchItemsCount
                                         maxId:self.currentPaginationInfo.nextMaxId
                                       success:^(NSArray *media, InstagramPaginationInfo *paginationInfo) {
                                           
                                           self.currentPaginationInfo = paginationInfo;

                                           [self.mediaArray addObjectsFromArray:media];
                                           [self.collectionView reloadData];
                                           
                                           [self.collectionView scrollToItemAtIndexPath:[NSIndexPath indexPathForItem:self.mediaArray.count - 1 inSection:0] atScrollPosition:UICollectionViewScrollPositionCenteredVertically animated:YES];

                                       }
                                       failure:^(NSError *error, NSInteger statusCode) {
                                           NSLog(@"Request Self Feed Failed");
                                       }];
}

- (void)requestSearchFeed: (NSString*) text
{
    [self.navigationItem.rightBarButtonItem setEnabled: NO];
    
    [self.instagramEngine getMediaWithTagName:text count:kFetchItemsCount maxId:nil
                                  //withSuccess:<#^(NSArray *media, InstagramPaginationInfo *paginationInfo)success#> failure:<#^(NSError *error, NSInteger serverStatusCode)failure#>]
//    [self.instagramEngine getSelfFeedWithCount:kFetchItemsCount
//                                         maxId:self.currentPaginationInfo.nextMaxId
                                       withSuccess:^(NSArray *media, InstagramPaginationInfo *paginationInfo) {
                                           
                                           self.currentPaginationInfo = paginationInfo;
                                           
                                           [self.mediaArray removeAllObjects];
                                           [self.mediaArray addObjectsFromArray:media];
                                           [self.collectionView reloadData];
                                           
                                           [self.collectionView scrollToItemAtIndexPath:[NSIndexPath indexPathForItem:self.mediaArray.count - 1 inSection:0] atScrollPosition:UICollectionViewScrollPositionCenteredVertically animated:YES];
                                           [self.navigationItem.rightBarButtonItem setEnabled: YES];
                                           [self.navigationItem.rightBarButtonItem setTitle:@"Play"];
                                           
                                       }
                                       failure:^(NSError *error, NSInteger statusCode) {
                                           NSLog(@"Request Self Feed Failed %@", error);
                                           [self.navigationItem.rightBarButtonItem setTitle:@"Error"];
                                       }];
}

/**
    Invoked when user taps the 'More' navigation item.
    @discussion The requestSelfFeed method is called with updated pagination parameters (nextMaxId).
 */
- (IBAction)moreTapped:(id)sender {
    [self.input resignFirstResponder];
    
    NSDate* creationDate = [NSDate date];
    creationDate = [creationDate dateByAddingTimeInterval:-(24*60*60)];
    int timeDelta = 1;

    NSMutableArray* items = [NSMutableArray array];
    
    for (InstagramMedia *media in self.mediaArray) {
        NSLog(@"%@", media.standardResolutionImageURL);
        
        NSString* urlString = media.standardResolutionImageURL.description;
        
        RTMediaItem* item = [[RTMediaItem alloc] initWithType:RTMediaTypePhoto
                                                   identifier:urlString];
        
        NSURL* url = media.standardResolutionImageURL;
        
        item.assetURL = url;
        // workaround BUG where thumbnail is been use to generate story
//        item.thumbnailURL = media.standardResolutionImageURL;
        item.thumbnailURL = media.thumbnailURL;
        
        item.creationDate = [creationDate dateByAddingTimeInterval:(5*60*timeDelta++)];
//        if (item.mediaType != RTMediaTypeVideo)
//        {
//            item.thumbnailURL = url;
//        }

        [items addObject:item];
    }
    
    RTStory* story = [[RTStory alloc] initWithType:RTStoryTypeHomeEvent
                                        mediaItems:items
                                             title:@"My remote story" titleIsDateBased:NO];
    
    RTStoryPlayer* player = [[RTStoryPlayer alloc] initWithAPIKey:API_KEY];
    
    // Create playback options
    NSMutableDictionary *options = [NSMutableDictionary dictionary];
    
    // This is how you would pass an authentication token to the player.
    NSData *myAuthToken = [[NSData alloc] init];	// replace with the real auth token
    [options setObject:myAuthToken forKey:RTOptionAuthenticationToken];
    
    //adding apps URL scheme so that we can return to the app after the story play is finished
    [options setObject:@"instareal://" forKey:RTOptionHostAppURLScheme];
    
    // allow auto install if player is not installed
    [options setObject:@YES forKey:RTOptionAllowAutoInstall];
    [options setObject:@"#2321233" forKey:RTOptionSubscriberId];
    
    NSError *error = nil;
    if ([player playWithStory:story options:options handler: self error:&error]) {
        NSLog(@"%@",[error description],nil);
    }

//    [self requestSelfFeed];
}
- (IBAction)editingChanged:(UITextField *)sender {
    NSLog(@"editingChanged %@", sender.text);
    
    if (sender.text.length > 0) {
        [self requestSearchFeed:sender.text];
    }
}

- (IBAction)valueChanged:(UITextField *)sender {
    NSLog(@"valueChanged %@", sender.text);
}

- (IBAction)editingDidBegin:(UITextField *)sender {
    NSLog(@"editingDidBegin %@", sender.text);
}

- (IBAction)editingDidEnd:(UITextField *)sender {
    NSLog(@"editingDidEnd %@", sender.text);
}

/**
    Invoked when user taps the left navigation item.
    @discussion Either directs to the Login ViewController or logs out.
 */
- (IBAction)loginTapped:(id)sender
{
    if (![self.instagramEngine isSessionValid]) {
        UINavigationController *loginNavigationViewController = [self.storyboard instantiateViewControllerWithIdentifier:@"LoginNavigationViewController"];
        [self presentViewController:loginNavigationViewController animated:YES completion:nil];
    }
    else
    {
        [self.instagramEngine logout];
        
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"InstagramKit" message:@"You are now logged out." delegate:nil cancelButtonTitle:@"Okay" otherButtonTitles:nil, nil];
        [alert show];
    }
}


#pragma mark - User Authenticated Notification -


- (void)userAuthenticationChanged:(NSNotification *)notification
{
    [self loadMedia];
}


#pragma mark - UIStoryboardSegue -


- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if ([segue.identifier isEqualToString:@"segue.media.detail"]) {
        IKMediaViewController *mediaViewController = (IKMediaViewController *)segue.destinationViewController;
        NSIndexPath *selectedIndexPath = [self.collectionView indexPathsForSelectedItems][0];
        InstagramMedia *media = self.mediaArray[selectedIndexPath.item];
        [mediaViewController setMedia:media];
    }
}

-(IBAction)unwindSegue:(UIStoryboardSegue *)sender
{
    [sender.sourceViewController dismissViewControllerAnimated:YES completion:nil];
}

#pragma mark - UICollectionViewDataSource Methods -


- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section
{
    return self.mediaArray.count;
}


- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath
{
    IKCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:@"CPCELL" forIndexPath:indexPath];
    InstagramMedia *media = self.mediaArray[indexPath.row];
    [cell setImageUrl:media.thumbnailURL];
    return cell;
}


- (void)updateCollectionViewLayout
{
    UICollectionViewFlowLayout *layout = (UICollectionViewFlowLayout *)self.collectionView.collectionViewLayout;
    CGFloat size = floor((CGRectGetWidth(self.collectionView.bounds)-1) / kNumberOfCellsInARow);
    layout.itemSize = CGSizeMake(size, size);
}

#pragma mark - RTPlaybackCompletionHandling members

- (void)storyPlayer:(RTStoryPlayer *)sender didFinishPlayback:(RTStory *)story storyModified:(BOOL)isStoryModified response:(RTStoryPlayerResponse *)response error:(NSError *)error
{
    // Check if there was an error and do nothing in that case.
    if(error != nil) {
        
        NSLog(@"Playback response error: %@", error);
        
        return;
    }
    
    /*
     * The user returned from the RealTimes app to our application.
     * We check whether the user saved some stories.
     */
    NSArray *savedStories = response.savedStories;
    if (savedStories.count != 0) {
        // Persist saved stories or do something with them.
    }
}

@end
