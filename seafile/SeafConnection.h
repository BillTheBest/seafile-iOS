//
//  SeafConnection.h
//  seafile
//
//  Created by Wang Wei on 10/11/12.
//  Copyright (c) 2012 Seafile Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

#define HTTP_ERR_LOGIN_REUIRED                  403
#define HTTP_ERR_LOGIN_INCORRECT_PASSWORD       400
#define HTTP_ERR_REPO_PASSWORD_REQUIRED         440


@class SeafConnection;
@class SeafRepos;
@class SeafRepo;
@class SeafUploadFile;

@protocol SSConnectionDelegate <NSObject>
- (void)connectionLinkingSuccess:(SeafConnection *)connection;
- (void)connectionLinkingFailed:(SeafConnection *)connection error:(int)error;
@end

@protocol SSConnectionAccountDelegate <NSObject>
- (void)getAccountInfoResult:(BOOL)result connection:(SeafConnection *)conn;
@end

@interface SeafConnection : NSObject
{
@private
    NSOperationQueue *queue;
}

@property (retain) NSMutableDictionary *info;
@property (nonatomic, copy) NSString *address;
@property (weak) id <SSConnectionDelegate> delegate;
@property (strong) SeafRepos *rootFolder;
@property (readonly) NSString *username;
@property (readonly) NSString *password;
@property (readonly) long long quota;
@property (readonly) long long usage;
@property (readwrite, strong) NSString *token;
@property (readonly) NSArray *seafGroups;
@property (readonly) NSArray *seafContacts;
@property (readwrite) int newreply;
@property (readwrite) int umsgnum;
@property (readwrite) int gmsgnum;


- (id)initWithUrl:(NSString *)url username:(NSString *)username;
- (void)loadRepos:(id)degt;

- (BOOL)localDecrypt:(NSString *)repoId;


- (void)sendRequest:(NSString *)url repo:(NSString *)repoId
            success:(void (^)(NSURLRequest *request, NSHTTPURLResponse *response, id JSON, NSData *data))success
            failure:(void (^)(NSURLRequest *request, NSHTTPURLResponse *response, NSError *error, id JSON))failure;

- (void)sendDelete:(NSString *)url repo:(NSString *)repoId
           success:(void (^)(NSURLRequest *request, NSHTTPURLResponse *response, id JSON, NSData *data))success
           failure:(void (^)(NSURLRequest *request, NSHTTPURLResponse *response, NSError *error, id JSON))failure;

- (void)sendPut:(NSString *)url repo:(NSString *)repoId form:(NSString *)form
        success:(void (^)(NSURLRequest *request, NSHTTPURLResponse *response, id JSON, NSData *data))success
        failure:(void (^)(NSURLRequest *request, NSHTTPURLResponse *response, NSError *error, id JSON))failure;


- (void)sendPost:(NSString *)url repo:(NSString *)repoId form:(NSString *)form
         success:(void (^)(NSURLRequest *request, NSHTTPURLResponse *response, id JSON, NSData *data))success
         failure:(void (^)(NSURLRequest *request, NSHTTPURLResponse *response, NSError *error, id JSON))failure;

- (void)loginWithAddress:(NSString *)anAddress username:(NSString *)username password:(NSString *)password;

- (void)getAccountInfo:(id<SSConnectionAccountDelegate>)degt;


- (void)getStarredFiles:(void (^)(NSHTTPURLResponse *response, id JSON, NSData *data))success
                failure:(void (^)(NSHTTPURLResponse *response, NSError *error, id JSON))failure;

- (id)getCachedStarredFiles;

- (void)getSeafGroups:(void (^)(NSHTTPURLResponse *response, id JSON, NSData *data))success
              failure:(void (^)(NSHTTPURLResponse *response, NSError *error, id JSON))failure;


- (BOOL)isStarred:(NSString *)repo path:(NSString *)path;

- (BOOL)setStarred:(BOOL)starred repo:(NSString *)repo path:(NSString *)path;

- (SeafRepo *)getRepo:(NSString *)repo;

- (SeafUploadFile *)getUploadfile:(NSString *)lpath;
- (void)removeUploadfile:(SeafUploadFile *)ufile;

- (void)search:(NSString *)keyword
       success:(void (^)(NSURLRequest *request, NSHTTPURLResponse *response, id JSON, NSMutableArray *results))success
       failure:(void (^)(NSURLRequest *request, NSHTTPURLResponse *response, NSError *error, id JSON))failure;

- (void)registerDevice:(NSData *)deviceToken;

@end
