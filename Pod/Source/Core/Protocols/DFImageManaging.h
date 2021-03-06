// The MIT License (MIT)
//
// Copyright (c) 2015 Alexander Grebenyuk (github.com/kean).
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

/*! For more info check the enumerations and other definitions provided in this header file:
 */
#import "DFImageManagerDefines.h"

@class DFImageRequest;
@class DFImageResponse;
@class DFImageTask;

typedef void (^DFImageTaskCompletion)(UIImage *__nullable image, NSError *__nullable error, DFImageResponse *__nullable response, DFImageTask *__nonnull imageTask);

/*! Provides a high-level API for loading images.
 */
@protocol DFImageManaging <NSObject>

/*! Inspects the given request and determines whether it can be handled.
 */
- (BOOL)canHandleRequest:(nonnull DFImageRequest *)request;

/*! Creates an image task with a given resource. After you create the task, you must start it by calling its resume method.
 @note Creates image request with a DFImageMaximumSize, DFImageContentModeAspectFill, and default options.
 @param completion Completion block to be called on the main thread when image task is either completed or cancelled. Completion block is called synchronously when the requested image can be retrieved from the memory cache and the request was made from the main thread. For more info see DFImageManager class reference.
 */
- (nonnull DFImageTask *)imageTaskForResource:(nonnull id)resource completion:(nullable DFImageTaskCompletion)completion;

/*! Creates an image task with a given request. After you create the task, you must start it by calling its resume method.
 @param request The request that contains the resource whose image is to be loaded, and additional options.
 @param completion Completion block to be called on the main thread when image task is either completed or cancelled. Completion block is called synchronously when the requested image can be retrieved from the memory cache and the request was made from the main thread. For more info see DFImageManager class reference.
 */
- (nonnull DFImageTask *)imageTaskForRequest:(nonnull DFImageRequest *)request completion:(nullable DFImageTaskCompletion)completion;

/*! Asynchronously calls a completion block on the main thread with all resumed outstanding image tasks and separate array with all preheating tasks.
 */
- (void)getImageTasksWithCompletion:(void (^__nullable)(NSArray *__nonnull tasks, NSArray *__nonnull preheatingTasks))completion;

/*! Cancels all outstanding requests, including preheating requests, and then invalidates the image manager. New image tasks may not be started.
 */
- (void)invalidateAndCancel;

/*! Prepares images for the given requests for later use.
 @note When you call this method, DFImageManager starts to fetch image data and cache images for the given requests. At any time afterward, you can create image tasks with equivalent requests.
 @note DFImageManager caches images with the exact target size, content mode, and options you specify in this method. If you later request an image with, for example, a different target size than you passed when calling this method, DFImageManager might have to generate a new image but would still be able to use cached image data.
 @note If this method is called twice with the same requests the second call would have no effect (unless first requests are completed).
 */
- (void)startPreheatingImagesForRequests:(nonnull NSArray /* DFImageRequest */ *)requests;

/*! Cancels preheating for the given requests.
 @note The request parameters shall exactly match the parameters used in startPreheatingImagesForRequests: method.
 */
- (void)stopPreheatingImagesForRequests:(nonnull NSArray /* DFImageRequest */ *)requests;

/*! Cancels all image preheating tasks registered with a manager.
 */
- (void)stopPreheatingImagesForAllRequests;

/*! Removes all cached images from all cache layers.
 */
- (void)removeAllCachedImages;

@end
