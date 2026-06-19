
/*
===============================================================================
LeetCode 355 - Design Twitter
Approach: Heap + Per User Tweet Storage
===============================================================================

IDEA
----

Instead of storing all tweets in one global array, we store tweets separately
for each user.

Example:

User 1:
(1,101)
(4,104)

User 2:
(2,102)
(5,105)

User 3:
(3,103)

Here the first value is the timestamp and the second value is the tweetId.

===============================================================================

WHY DO WE TAKE ONLY THE LAST TWEET OF EACH USER?
------------------------------------------------

Suppose User 1 follows User 2 and User 3.

Initially we only care about the MOST RECENT tweet of every relevant user.

User 1 latest tweet -> (4,104)
User 2 latest tweet -> (5,105)
User 3 latest tweet -> (3,103)

Why?

Because if a user's latest tweet is not selected yet, there is no reason to
look at his older tweets.

For example:

User 2:
(2,102)
(5,105)

If 105 is still available, 102 can never be chosen before it.

Therefore initially we push only the latest tweet of:
- the user himself
- all users he follows

into a max heap.

===============================================================================

WHAT HAPPENS AFTER WE REMOVE A TWEET?
-------------------------------------

Suppose the heap gives:

(5,105)

This tweet belongs to User 2.

Now User 2's latest tweet has been consumed.

So the next candidate from User 2 becomes:

(2,102)

We insert it into the heap.

This way the heap always contains the latest remaining tweet of every user.

===============================================================================

HEAP NODE FORMAT
----------------

{
    timestamp,
    tweetId,
    index,
    userId
}

Example:

{
    5,
    105,
    1,
    2
}

Meaning:

timestamp = 5
tweetId   = 105
index     = 1 inside tweets[2]
userId    = 2

The index helps us move to the previous tweet of the same user.

===============================================================================

COMPLEXITY
----------

postTweet()  : O(1)

follow()     : O(log n)

unfollow()   : O(log n)

getNewsFeed():

Heap size is at most:

(number of followees + 1)

At most 10 tweets are extracted.

Time Complexity:

O((F + 10) log F)

where F = number of followees.

===============================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Twitter {

    unordered_map<int,vector<pair<int,int>>> tweets;
    unordered_map<int,set<int>> follows;

    int counter = 1;

public:

    Twitter() {

    }

    void postTweet(int userId, int tweetId) {

        tweets[userId].push_back({counter,tweetId});
        counter++;
    }

    vector<int> getNewsFeed(int userId) {

        vector<int> fans;

        priority_queue<vector<int>> pq;

        // Push latest tweet of current user
        if(!tweets[userId].empty()) {

            int idx = tweets[userId].size()-1;

            pq.push({
                tweets[userId][idx].first,
                tweets[userId][idx].second,
                idx,
                userId
            });
        }

        // Push latest tweet of every followee
        for(auto followee : follows[userId]) {

            if(tweets[followee].empty())
                continue;

            int idx = tweets[followee].size()-1;

            pq.push({
                tweets[followee][idx].first,
                tweets[followee][idx].second,
                idx,
                followee
            });
        }

        while(!pq.empty() && fans.size() < 10) {

            auto cur = pq.top();
            pq.pop();

            int tweetId = cur[1];
            int idx     = cur[2];
            int user    = cur[3];

            fans.push_back(tweetId);

            // Move to previous tweet of same user
            idx--;

            if(idx >= 0) {

                pq.push({
                    tweets[user][idx].first,
                    tweets[user][idx].second,
                    idx,
                    user
                });
            }
        }

        return fans;
    }

    void follow(int followerId, int followeeId) {

        follows[followerId].insert(followeeId);
    }

    void unfollow(int followerId, int followeeId) {

        follows[followerId].erase(followeeId);
    }
};

