int copy_directory_contents(struct File *src, struct File *dst) {
   struct File *dir_content;
   void *blk;
   int r;
   // Iterate over each block in the source directory
   for (u_int i = 0; i < ROUND(src->f_size, BLOCK_SIZE) / BLOCK_SIZE; i++) {
   if ((r = file_get_block(src, i, &blk)) < 0) {
         return r;
      }
      dir_content = (struct File *)blk;
      for (int j = 0; j < FILE2BLK; j++) {
         if (dir_content[j].f_name[0] == '\0') continue;
         struct File *dst_file;
         // Step1: Alloc dst_file using 'dir_alloc_file'
         // Lab 5-2-Exam: Your code here. (4/6)

         // Step2: Assign corresponding values of 'f_name', 'f_dir', 'f_size', 'f_type' to dst_file
         strcpy(dst_file->f_name, dir_content[j].f_name);
         dst_file->f_dir = dst;
         dst_file->f_size = dir_content[j].f_size;
         dst_file->f_type = dir_content[j].f_type;

         // Step3: Invoke either 'copy_directory_contents' or 'copy_file_content',
         // depending on the value of 'f_type'.
         // Lab 5-2-Exam: Your code here. (5/6)

      }
   }
   file_flush(dst);
   return 0;
}

int directory_copy(char *src_path, char *dst_path) {
   struct File *src_dir, *dst_dir;
   int r;
   if ((r = file_open(src_path, &src_dir)) < 0) {
      return r;
   }
   if ((r = file_create(dst_path, &dst_dir)) < 0) {
      return r;
   }
   dst_dir->f_type = FTYPE_DIR;
   return copy_directory_contents(src_dir, dst_dir);
}
