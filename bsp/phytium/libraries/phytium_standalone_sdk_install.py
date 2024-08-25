import os
import subprocess

def clone_repository(branch, commit_hash):
    repository_url = "https://gitee.com/phytium_embedded/phytium-standalone-sdk.git"
    target_folder =  "../libraries/phytium_standalone_sdk"

    # Clone the repository
    subprocess.call(["git", "clone", "-b", branch, repository_url, target_folder])

    # Change to the cloned repository folder
    os.chdir(target_folder)

    # Checkout the specific commit
    subprocess.call(["git", "checkout", commit_hash])

    print("Repository cloned successfully to {}".format(os.getcwd()))

if __name__ == "__main__":

    branch_to_clone = "master"
    commit_to_clone = "3a353d48ee1db27acf77241a62fb7e35c779e110"

    clone_repository(branch_to_clone, commit_to_clone)