#run.sh

export VULKAN_ROOT_LOCATON="$HOME/Documents/Projects/"
export VULKAN_SDK_VERSION="1.1.73.0"
export VULKAN_SDK="$VULKAN_ROOT_LOCATON/vulkansdk-macos-$VULKAN_SDK_VERSION/macOS"
export VK_ICD_FILENAMES="$VULKAN_SDK/etc/vulkan/icd.d/MoltenVK_icd.json"
export VK_LAYER_PATH="$VULKAN_SDK/etc/vulkan/explicit_layers.d" 
export PATH="/usr/local/opt/python/libexec/bin:$VULKAN_SDK/bin:$PATH"
