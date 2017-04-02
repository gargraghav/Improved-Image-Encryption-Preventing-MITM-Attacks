# Implementation Process

**Step 1:** _Reading the image file_

Used the QDBMP library for handling BMP image files.The library supports the following BMP variants
- Uncompressed 32 BPP (alpha values are ignored)
- Uncompressed 24 BPP
- Uncompressed 8 BPP (indexed color)

**Step 2:** _Shuffling the pixel values_

In order to decrease correlation between two adjoining pixels of an image, position of the pixels in the original image is shuffled.
So, the input image (N X M) is scrambled according to a randomly generated new coordinate value for each pixel or a block of pixels.

**Step 3:** _Key Generation_

A pair of encryption and decryption keys need to be generated for an image in order to perform mathematical/statistical encryption strategies. More the bit-length of the key, more difficult it gets to break the cipher using Brute-Force and also makes it secure against Known Plain-Text Attacks.

**Step 4:** _Encryption_

Encrypt each pixel value ‘m’ contained in the image 2D matrix using: 
- CipherValue = (m.pow(e)).mod(N).

**Step 5:** _Decryption_

Decrypt each pixel value ‘m’ contained in the encrypted 2D matrix using:
- m = (CipheValue.pow(d)).mod(N).

**Step 6:**  _Histogram Analysis_

An Image Histogram gives a graphical representation of the tonal distribution in a digital image by plotting number of pixels for each tonal value.
