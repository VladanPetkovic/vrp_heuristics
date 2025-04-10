import os


def file_exists(file_path):
    return os.path.isfile(file_path)


def dir_exists(dir_path):
    return os.path.isdir(dir_path)


def get_file_name_from_path(file_path):
    file_name = os.path.basename(file_path)
    file_name_without_ext = os.path.splitext(file_name)[0]
    return file_name_without_ext
