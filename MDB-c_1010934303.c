/*
 *  CSC A48 - Assignment 1 starter

 */

/* Student identification:
 * 
 * Student Name (Last name, First name): Kamal Zuairia Binte
 * Student Number: 1010934303
 * UTORid: kamalzua
 * Your instructor's name is: Rawad Abou Assi
 */

/* Academic Integrity Statement:
 * 
 * I hereby certify that the work contained in this file is my own, and
 * that I have not received any parts of my solution from other sources
 * including my fellow students, external tutoring services, the internet,
 * or algorithm implementations found online.
 * 
 * Sign here with your name: Zuairia Binte Kamal
 *
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR_LEN 1024




typedef struct CastList {
    char name[MAX_STR_LEN];
    float salary;
    struct CastList *next;
} CastList;

typedef struct MovieReview {
    char movie_title[MAX_STR_LEN];
    char movie_studio[MAX_STR_LEN];
    int year;
    float BO_total;
    int score;
    CastList *cast;
} MovieReview;

typedef struct ReviewNode {
    MovieReview review;
    struct ReviewNode *next;
} ReviewNode;

ReviewNode *newMovieReviewNode(const char *movie_title, const char *movie_studio, int year, float BO_total, int score) {

    

    ReviewNode *newNode = (ReviewNode *)malloc(sizeof(ReviewNode));
    if (!newNode) return NULL;

    strcpy(newNode->review.movie_title, movie_title);
    strcpy(newNode->review.movie_studio, movie_studio);
    newNode->review.year = year;
    newNode->review.BO_total = BO_total;
    newNode->review.score = score;
    newNode->review.cast = NULL;
    newNode->next = NULL;

    return newNode;
}

ReviewNode *findMovieReview(const char *movie_title, const char *movie_studio, int year, ReviewNode *head) {
     
    
    while (head) {
        if (strcmp(head->review.movie_title, movie_title) == 0 && 
            strcmp(head->review.movie_studio, movie_studio) == 0 && 
            head->review.year == year) 
            return head;
        head = head->next;
    }
    return NULL;
}

ReviewNode *insertMovieReview(const char *movie_title, const char *movie_studio, int year, float BO_total, int score, ReviewNode *head) {

    

    if (findMovieReview(movie_title, movie_studio, year, head) != NULL)
        return head;

    ReviewNode *newNode = newMovieReviewNode(movie_title, movie_studio, year, BO_total, score);
    if (!newNode) return head;

    newNode->next = head;
    return newNode;
}

int countReviews(ReviewNode *head) {

    
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

int updateMovieReview(const char *movie_title, const char *movie_studio, int year, float BO_total, int newScore, ReviewNode *head) {

    

    ReviewNode *node = findMovieReview(movie_title, movie_studio, year, head);
    if (!node) return 0;
    
    node->review.score = newScore;
    node->review.BO_total = BO_total;
    return 1;
}

ReviewNode *deleteMovieReview(const char *movie_title, const char *movie_studio, int year, ReviewNode *head) {

   

    ReviewNode *current = head, *prev = NULL;
    
    while (current) {
        if (strcmp(current->review.movie_title, movie_title) == 0 && 
            strcmp(current->review.movie_studio, movie_studio) == 0 && 
            current->review.year == year) {
            if (prev) prev->next = current->next;
            else head = current->next;
            
            free(current);
            return head;
        }
        prev = current;
        current = current->next;
    }
    return head;
}

void printMovieReviews(ReviewNode *head) {

        

    while (head) {
        printf("%s\n%s\n%d\n%f\n%d\n**********************\n", 
            head->review.movie_title, head->review.movie_studio, head->review.year, head->review.BO_total, head->review.score);
        head = head->next;
    }
}

void queryReviewsByStudio(const char *movie_studio, ReviewNode *head) {

    

    while (head) {
        if (strcmp(head->review.movie_studio, movie_studio) == 0) {
            printf("%s (%d) - Score: %d\n", head->review.movie_title, head->review.year, head->review.score);
        }
        head = head->next;
    }
}

ReviewNode *queryReviewsByScore(int score, ReviewNode *head) {

   

    while (head) {
        if (head->review.score == score) {
            printf("%s (%d) - movie_studio: %s\n", head->review.movie_title, head->review.year, head->review.movie_studio);
        }
        head = head->next;
    }
    return head;
}

ReviewNode *deleteReviewList(ReviewNode *head) {

    
    while (head) {
        ReviewNode *temp = head;
        
        CastList *cast = temp->review.cast;
        while (cast) {
            CastList *tempCast = cast;
            cast = cast->next;
            free(tempCast);
        }

        head = head->next;
        free(temp);
    }
    return NULL;
}



ReviewNode *sortReviewsByTitle(ReviewNode *head) {

    

    if (!head || !head->next) return head;

    int swapped;
    ReviewNode *ptr1, *lptr = NULL;
    do {
        swapped = 0;
        ptr1 = head;
        while (ptr1->next != lptr) {
            if (strcmp(ptr1->review.movie_title, ptr1->next->review.movie_title) > 0) {
                MovieReview temp = ptr1->review;
                ptr1->review = ptr1->next->review;
                ptr1->next->review = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    
    return head;
}

int insertCastMember(const char *movie_title, const char *studio, int year, ReviewNode *head, const char *name, float salary) {
    
  

    ReviewNode *node = findMovieReview(movie_title, studio, year, head);
    if (!node) return 0;

    CastList *newCast = (CastList *)malloc(sizeof(CastList));
    if (!newCast) return 0;

    strcpy(newCast->name, name);
    newCast->salary = salary;

    newCast->next = node->review.cast;
    node->review.cast = newCast;

    return 1;
}

void whosTheStar(ReviewNode *head) {     


    struct {
        char name[MAX_STR_LEN];
        float earnings;
    } topActor = {"", 0};

    while (head) {
        CastList *cast = head->review.cast;
        while (cast) {
            if (topActor.earnings < head->review.BO_total) {
                strcpy(topActor.name, cast->name);
                topActor.earnings = head->review.BO_total;
            }
            cast = cast->next;
        }
        head = head->next;
    }

    if (topActor.earnings > 0)
        printf("Top actor: %s with earnings %.2f\n", topActor.name, topActor.earnings);
    else
        printf("No cast data available.\n");
}

void printNames(ReviewNode *movie) {
    if (!movie) {
        printf("Movie not found!\n");
        return;
    }

    CastList *cast = movie->review.cast;
    if (!cast) {
        printf("No cast members found for this movie.\n");
        return;
    }

    printf("Cast members for %s:\n", movie->review.movie_title);
    while (cast) {
        printf("  - %s (Salary: $%.2f)\n", cast->name, cast->salary);
        cast = cast->next;
    }
}
