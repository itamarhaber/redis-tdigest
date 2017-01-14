/*
 * include/tdigest.c
 *
 * Copyright (c) 2016, Usman Masood <usmanm at fastmail dot fm>
 */

#ifndef TDIGEST_H
#define TDIGEST_H

#define DEFAULT_COMPRESSION 400

struct Centroid {
    long long weight;
    double mean;
};

struct Point {
    double value;
    long long weight;
    struct Point *next;
};

struct TDigest {
    double compression;
    int threshold;
    long long size;

    long long total_weight;
    double min;
    double max;

    int num_buffered_pts;
    struct Point *buffered_pts;

    int num_centroids;
    struct Centroid *centroids;
};

extern struct TDigest *tdigestNew(int compression);
extern void tdigestAdd(struct TDigest *t, double x, long long w);
extern void tdigestMerge(struct TDigest *t1, struct TDigest *t2);
extern double tdigestCDF(struct TDigest *t, double x);
extern double tdigestQuantile(struct TDigest *t, double q);
extern void tdigestCompress(struct TDigest *t);
extern void tdigestFree(struct TDigest *t);

#endif /* TDIGEST_H */
