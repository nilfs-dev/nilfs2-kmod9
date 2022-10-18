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
#  if (RHEL_RELEASE_N >= 120)
#   define	HAVE_NEW_BIO_ALLOC		1
#   define	HAVE_BD_SPLIT_DISCARD		1
#  endif
# else /* !defined(RHEL_RELEASE_N) */
#  define	HAVE_BD_BDI			0
#  define	HAVE_BDEV_NR_BYTES		1
#  if (RHEL_MINOR > 0)				/* RHEL_RELEASE_N >= 71 */
#   define	HAVE_NEW_BIO_ALLOC		1
#   define	HAVE_BD_SPLIT_DISCARD		1
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
 * bdev_nr_bytes() helper was added in kernel 5.15.
 */
#ifndef HAVE_BDEV_NR_BYTES
# define HAVE_BDEV_NR_BYTES \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(5, 15, 0))
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
 * The secure erase operation was split out of discard operation
 * in kernel 5.18 and later.
 */
#ifndef HAVE_BD_SPLIT_DISCARD
# define HAVE_BD_SPLIT_DISCARD \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(5, 18, 0))
#endif
#endif /* LINUX_VERSION_CODE */


#include <linux/blkdev.h>
#include <linux/fs.h>

#if !HAVE_BDEV_NR_BYTES
static inline loff_t bdev_nr_bytes(struct block_device *bdev)
{
	return i_size_read(bdev->bd_inode);
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

#endif /* NILFS_KERN_FEATURE_H */
