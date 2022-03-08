## Machine Learning on IMU and Audio

#### Task 1 (40 pts)
- IMU - Wave and Fist Bump - Machine Learning Model

We are going to develop a supervised machine learning model for Wave and Fist Bump gestures. Here we are going to use the `sk-learn` library to build the model.

- Access your data from the data dropbox folder.
    - https://www.dropbox.com/sh/xhjg84o66bifbcl/AADDD5oHcn89zbD7yUkv2Enua?dl=0
    - password: `tinyML`
- You need to read in both files and process the data with different labels **Y** for the different gestures.
- Pre-process your data to create the feature matrices for your **X**. For IMU each observation should have a shape 119x6.
- Build three machine learning models - 1) Logistic Regression, 2) Decision Trees, and 3) Random Forests
    - Use train test split of 80-20
- Report Precision, Recall, F1 Score, and Confusion Matrix
    - Discuss bias and variance characteristics.

#### Task 2 (40 pts)
- Audio - Up and Down/ Stop and Go - Machine Learning Model

This task is very similar to the above one. The only difference here is the number of datapoints and the different classes. We are going to build a supervised machine learning model for Audio.

- Access your data from the data dropbox folder.
    - https://www.dropbox.com/sh/xhjg84o66bifbcl/AADDD5oHcn89zbD7yUkv2Enua?dl=0
    - password: `tinyML`
- You need to read in both files and process the data with different labels **Y** for the different gestures.
- Pre-process your data to create the feature matrices for your **X**. For Audio each observation should have a shape 1x64.
- Build three machine learning models - 1) Logistic Regression, 2) Decision Trees, and 3) Random Forests
    - Use train test split of 80-20
- Report Precision, Recall, F1 Score, and Confusion Matrix


#### Task 3 (30 pts)

Here develop models using the entire class data. You will need to read each folder and then create the features for IMU model and Audio model. Develop this out as separate notebooks. Perform the same steps for each of the models as above.


### Deliverable
- Github Assignment (your repository)
    - Source code in /src
        - Upload you jupyter notebooks with proper description and references.
            - 4 notebooks - 1. IMU own data, 2. Audio own data, 3. IMU class data, 4. Audio class data.
        - Have proper section headings within your notebooks for pre-processing, modeling and results.
        - Your notebooks should contain all of the results and description of what you have obeserved from those results. Presenting just the results is not enough.
- Put the link of the assignment on Canvas
