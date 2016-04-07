from skimage.filter import threshold_otsu
from skimage import io
from skimage.filter.rank import median
from skimage.morphology import disk,skeletonize,medial_axis,remove_small_objects
import matplotlib.pyplot as plt


input_image = io.imread('test1.jpg',
                    as_grey=True, plugin=None, flatten=None)
image = median(input_image, disk(15)) 

thresh = threshold_otsu(image)
image = image < thresh

skel1=skeletonize(image)
skel2=medial_axis(image)

min_size=sum(sum(skel1))/2

remove_small_objects(skel1,min_size=min_size,connectivity=5,in_place=True)

remove_small_objects(skel2,min_size=min_size,connectivity=5,in_place=True)


fig2, ax = plt.subplots(2, 2, figsize=(24, 12))

ax[0,0].imshow(input_image,cmap=plt.cm.gray)
ax[0,0].set_title('Input image')
ax[0,0].axis('image')
ax[0,1].imshow(image, cmap=plt.cm.gray)
ax[0,1].set_title('Binary image')
ax[0,1].axis('image')
ax[1,0].imshow(skel1, cmap=plt.cm.gray)
ax[1,0].set_title('Skeleton')
ax[1,0].axis('image')
ax[1,1].imshow(skel2,cmap=plt.cm.gray)
ax[1,1].set_title('Sleleton - Medial axis')
ax[1,1].axis('image')

plt.show()


print ("Length 1: {0}".format(sum(sum(skel1))))
print ("Length 2: {0}".format(sum(sum(skel2))))
