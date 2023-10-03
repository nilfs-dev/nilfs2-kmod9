/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Kernel dependent features
 */

#ifndef NILFS_KERN_FEATURE_H
#define NILFS_KERN_FEATURE_H

#include <linux/version.h>
#ifndef LINUX_VERSION_CODE
# include <generated/uapi/linux/version.h>
#endif

/*
 * Please define as 0/1 here if you want to override
 */

/*
 * for Red Hat Enterprise Linux 9.x clones
 */
#if defined(RHEL_MAJOR) && (RHEL_MAJOR == 9)
# if defined(RHEL_RELEASE_N)
#  if (RHEL_RELEASE_N >= 34)
#   define	HAVE_BD_BDI			0
#   define	HAVE_BDEV_NR_BYTES		1
#  endif
#  define	HAVE_ALLOC_INODE_SB		(RHEL_RELEASE_N >= 92)
#  if (RHEL_RELEASE_N >= 120)
#   define	HAVE_NEW_BIO_ALLOC		1
#   define	HAVE_BD_SPLIT_DISCARD		1
#   define	HAVE_BDEV_DISCARD_HELPERS	1
#  endif
#  if (RHEL_RELEASE_N >= 183)
#   define	HAVE_AOPS_INVALIDATE_FOLIO	1
#   define	HAVE_AOPS_DIRTY_FOLIO		1
#   define	HAVE_BDI_WRITE_CONGESTED	0
#   define	HAVE_BLK_OPF_T			1
#  endif
#  if (RHEL_RELEASE_N >= 293)
#   define	HAVE_AOPS_READ_FOLIO		1
#   define	HAVE_WRITE_BEGIN_FLAGS		0
#   define	HAVE_FILEMAP_GET_FOLIOS		1
#  endif
#  if (RHEL_RELEASE_N >= 295)
#   define	HAVE_TIMER_SHUTDOWN_SYNC	1
#  endif
#  if (RHEL_RELEASE_N >= 370)
#   define	HAVE_NEW_BLKDEV_GET_AND_PUT	1
#   define	HAVE_SB_S_MODE			0
#   define	HAVE_BLK_MODE_T			1
#  endif
# else /* !defined(RHEL_RELEASE_N) */
#  define	HAVE_BD_BDI			0
#  define	HAVE_BDEV_NR_BYTES		1
#  if (RHEL_MINOR > 0)				/* RHEL_RELEASE_N >= 71 */
#   define	HAVE_NEW_BIO_ALLOC		1
#   define	HAVE_BD_SPLIT_DISCARD		1
#   define	HAVE_BDEV_DISCARD_HELPERS	1
#   define	HAVE_ALLOC_INODE_SB		1
#  endif
#  if (RHEL_MINOR > 1)				/* RHEL_RELEASE_N >= 163 */
#   define	HAVE_AOPS_INVALIDATE_FOLIO	1
#   define	HAVE_AOPS_DIRTY_FOLIO		1
#   define	HAVE_BDI_WRITE_CONGESTED	0
#   define	HAVE_BLK_OPF_T			1
#  endif
#  if (RHEL_MINOR > 2)				/* RHEL_RELEASE_N >= 285 */
#   define	HAVE_AOPS_READ_FOLIO		1
#   define	HAVE_WRITE_BEGIN_FLAGS		0
#   define	HAVE_FILEMAP_GET_FOLIOS		1
#   define	HAVE_TIMER_SHUTDOWN_SYNC	1
#  endif
#  if (RHEL_MINOR > 3)				/* RHEL_RELEASE_N >= 363 */
#   define	HAVE_NEW_BLKDEV_GET_AND_PUT	1
#   define	HAVE_SB_S_MODE			0
#   define	HAVE_BLK_MODE_T			1
#  endif
# endif
#endif

/*
 * defaults
 */

/*
 * defaults dependent to kernel versions
 */
#ifdef LINUX_VERSION_CODE
/*
 * bd_bdi member was removed from struct block_device in kernel 5.15.
 */
#ifndef HAVE_BD_BDI
# define HAVE_BD_BDI \
	(LINUX_VERSION_CODE < KERNEL_VERSION(5, 15, 0))
#endif
/*
 * bdev_nr_bytes() and sb_bdev_nr_blocks() helpers were added in kernel 5.16.
 */
#ifndef HAVE_BDEV_NR_BYTES
# define HAVE_BDEV_NR_BYTES \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(5, 16, 0))
#endif
/*
 * The arguments of bio_alloc() was extended to recieve block_device,
 * opf and operation in kernel 5.17.
 */
#ifndef HAVE_NEW_BIO_ALLOC
# define HAVE_NEW_BIO_ALLOC \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(5, 17, 0))
#endif
/*
 * The invalidatepage operation was replaced with invalidate_folio
 * in address space operations and block_invalidate_folio() was
 * introduced to alter block_invalidatepage() in kernel 5.17.
 */
#ifndef HAVE_AOPS_INVALIDATE_FOLIO
# define HAVE_AOPS_INVALIDATE_FOLIO \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(5, 17, 0))
#endif
/*
 * The set_page_dirty operation was replaced with dirty_folio in
 * address space operations in kernel 5.17.
 */
#ifndef HAVE_AOPS_DIRTY_FOLIO
# define HAVE_AOPS_DIRTY_FOLIO \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(5, 17, 0))
#endif
/*
 * bdi_write_congested() was removed in kernel 5.18.
 */
#ifndef HAVE_BDI_WRITE_CONGESTED
# define HAVE_BDI_WRITE_CONGESTED \
	(LINUX_VERSION_CODE < KERNEL_VERSION(5, 18, 0))
#endif
/*
 * The secure erase operation was split out of discard operation
 * in kernel 5.18 and later.
 */
#ifndef HAVE_BD_SPLIT_DISCARD
# define HAVE_BD_SPLIT_DISCARD \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(5, 18, 0))
#endif
/*
 * A few block_device based helpers were added in kernel 5.18 to
 * abstract parameter retrieval for discard operations.
 */
#ifndef HAVE_BDEV_DISCARD_HELPERS
# define HAVE_BDEV_DISCARD_HELPERS \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(5, 18, 0))
#endif
/*
 * alloc_inode_sb() was introduced to allocate filesystem specific
 * inode in kernel 5.18.
 */
#ifndef HAVE_ALLOC_INODE_SB
# define HAVE_ALLOC_INODE_SB \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(5, 18, 0))
#endif
/*
 * The request operation type and the request flags were combined and
 * then replaced with blk_opf_t type in kernel 5.19.
 */
#ifndef HAVE_BLK_OPF_T
# define HAVE_BLK_OPF_T \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(5, 19, 0))
#endif
/*
 * The readpage operation was replaced with read_folio in
 * address space operations in kernel 5.19.
 */
#ifndef HAVE_AOPS_READ_FOLIO
# define HAVE_AOPS_READ_FOLIO \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(5, 19, 0))
#endif
/*
 * The flags argument was removed from block_write_begin helper function
 * and write_begin operation of address space operations in kernel 5.19.
 */
#ifndef HAVE_WRITE_BEGIN_FLAGS
# define HAVE_WRITE_BEGIN_FLAGS \
	(LINUX_VERSION_CODE < KERNEL_VERSION(5, 19, 0))
#endif
/*
 * filemap_get_folios() was added in kernel 6.0 to replace
 * pagevec_lookup().
 */
#ifndef HAVE_FILEMAP_GET_FOLIOS
# define HAVE_FILEMAP_GET_FOLIOS \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(6, 0, 0))
#endif
/*
 * timer_shutdown_sync() was added in kernel 6.2 to reliably
 * deactivate timer for teardown situations.
 */
#ifndef HAVE_TIMER_SHUTDOWN_SYNC
# define HAVE_TIMER_SHUTDOWN_SYNC \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(6, 2, 0))
#endif
/*
 * In kernel 6.5, an argument was added to blkdev_get_by_*() that takes
 * a pointer to a blk_holder_ops structure for exclusive claims, and
 * blkdev_put() has been changed not to use FMODE_EXCL flag.
 */
#ifndef HAVE_NEW_BLKDEV_GET_AND_PUT
# define HAVE_NEW_BLKDEV_GET_AND_PUT \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(6, 5, 0))
#endif
/*
 * sb->s_mode was removed in kernel 6.5.
 */
#ifndef HAVE_SB_S_MODE
# define HAVE_SB_S_MODE \
	(LINUX_VERSION_CODE < KERNEL_VERSION(6, 5, 0))
#endif
/*
 * In kernel 6.5, regarding block open flags, fmode_t has been replaced
 * with block-specific type (BLK_OPEN_*) and sb_open_mode() helper has
 * been added to simplify calculating its value from mount flags.
 */
#ifndef HAVE_BLK_MODE_T
# define HAVE_BLK_MODE_T \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(6, 5, 0))
#endif
#endif /* LINUX_VERSION_CODE */


#include <linux/blkdev.h>
#include <linux/fs.h>
#include <linux/buffer_head.h>
#include <linux/timer.h>

#if !HAVE_TIMER_SHUTDOWN_SYNC
static inline int timer_shutdown_sync(struct timer_list *timer)
{
	return del_timer_sync(timer);
}
#endif

#if !HAVE_BDEV_NR_BYTES
static inline loff_t bdev_nr_bytes(struct block_device *bdev)
{
	return i_size_read(bdev->bd_inode);
}

static inline u64 sb_bdev_nr_blocks(struct super_block *sb)
{
	return (u64)bdev_nr_bytes(sb->s_bdev) >> sb->s_blocksize_bits;
}
#endif

static inline int
compat_blkdev_issue_discard(struct block_device *bdev, sector_t sector,
			    sector_t nr_sects, gfp_t gfp_mask,
			    unsigned long flags)
{
#if HAVE_BD_SPLIT_DISCARD
	return blkdev_issue_discard(bdev, sector, nr_sects, gfp_mask);
#else
	return blkdev_issue_discard(bdev, sector, nr_sects, gfp_mask, flags);
#endif
}

#if !HAVE_BDEV_DISCARD_HELPERS
static inline unsigned int bdev_max_discard_sectors(struct block_device *bdev)
{
	return bdev_get_queue(bdev)->limits.max_discard_sectors;
}

static inline unsigned int bdev_discard_granularity(struct block_device *bdev)
{
	return bdev_get_queue(bdev)->limits.discard_granularity;
}
#endif

#if !HAVE_ALLOC_INODE_SB
static inline void *
alloc_inode_sb(struct super_block *sb, struct kmem_cache *cache, gfp_t gfp)
{
	return kmem_cache_alloc(cache, gfp);
}
#endif

static inline int
compat_submit_bh(int mode, int mode_flags, struct buffer_head *bh)
{
#if HAVE_BLK_OPF_T
	return submit_bh(mode | mode_flags, bh);
#else
	return submit_bh(mode, mode_flags, bh);
#endif
}

#if HAVE_NEW_BLKDEV_GET_AND_PUT
#define compat_blkdev_get_by_path(dev_name, mode, holder, hops) \
	blkdev_get_by_path(dev_name, mode, holder, hops)
#define compat_blkdev_put(bdev, mode, holder) \
	blkdev_put(bdev, holder)
#else
#define compat_blkdev_get_by_path(dev_name, mode, holder, hops) \
	blkdev_get_by_path(dev_name, mode, holder)
#define compat_blkdev_put(bdev, mode, holder) \
	blkdev_put(bdev, mode)
#endif

#if !HAVE_BLK_MODE_T
typedef fmode_t blk_mode_t;
#define sb_open_mode(flags) \
	(FMODE_READ | FMODE_EXCL | (((flags) & SB_RDONLY) ? 0 : FMODE_WRITE))
#endif

#endif /* NILFS_KERN_FEATURE_H */
