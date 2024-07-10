#include <stdio.h>
#include <unistd.h>
 #include <sys/vfs.h> 
 
int check_sdcard_fstype(void)
{
	struct statfs s;
	
	statfs("/tmp/SD0", &s);
  	return s.f_type;
}

int check_rootfs_fstype(void)
{
	static int rootfstype = 0;
	if (0 == rootfstype)
	{
		struct statfs s;

		statfs("/tmp", &s);
		rootfstype = s.f_type;
	}
	return rootfstype;
}

int check_storage_total_and_free(int *f, int *t)
{
	struct statfs s;
	int statfs_ret;
	const char *sd_dir = "/dev/mmcblk0";

	if (NULL == f || NULL == t)
	{
		return -1;
	}

	if (access(sd_dir, F_OK) != 0) // no card insert
	{
		*f = 0;
		*t = 0;
		return 0;
	}

	statfs_ret = statfs("/sdcard/", &s);
	if (statfs_ret != 0)
	{
		*f = 0;
		*t = 0;
		return 0;
	}
	if (s.f_type == check_rootfs_fstype())
	{
		*f = 0;
		*t = 0;
		return 0;
	}
	*f = (s.f_bsize >> 10) * s.f_bavail;//Kb
	*t = (s.f_bsize >> 10) * s.f_blocks;//Kb
	return 0;
}

int check_storage_freespace(void)
{
	struct statfs s;
	int free_bsz;
	int statfs_ret;
	const char *sd_dir = "/dev/mmcblk0";

	if (access(sd_dir, F_OK) != 0) // no card insert
	{
		return 0;
	}

	statfs_ret = statfs("/sdcard/", &s);
	if (statfs_ret != 0)
	{
		return 0;
	}

	if (s.f_type == check_rootfs_fstype())
	{
		return 0;
	}
	free_bsz = (s.f_bsize >> 8) * s.f_bavail;
	return (free_bsz >> 12); // MiB
}

int check_storage_totalspace(void)
{
	struct statfs s;
	int free_bsz;

	statfs("/sdcard/", &s);
	if (s.f_type == check_rootfs_fstype())
	{
		return 0;
	}
	free_bsz = (s.f_bsize >> 8) * s.f_blocks;
	return (free_bsz >> 12); // MiB
}

int main()
{
	int sdcard_fstype = check_sdcard_fstype();
	int rootfstype = check_rootfs_fstype();
	if(sdcard_fstype != rootfstype)
		printf("card is formatted\n");
	else
		printf("card is not formatted\n");
	return 0;
}