# TeamProject: Shall we cook?

# Content Structure
We have two sections under the project: the first one is the prototype, and the second is the images.

* Under the prototype, we have Arduino code and HTML files.

* For the images, we have separated them into four stages. All the work details from our Miro Board was downlarded as image, all these materials are documented in the timeline order.

# Function

# Guidelines for use
**Please refer to [prototype video](https://youtu.be/z_AU-Dssteg?si=0W-s1Vil3uGfOGYu) to see how our prototype works.**

# Figma Prototype & Handmade Smartphone Projector

The Figma prototype was used for screens on both [shared screen projections](https://www.figma.com/proto/X5FIVdsP2S1bFrMx241lQ5/DECO3500-Progress-UI---Final-ver?page-id=0%3A1&node-id=2346-28127&node-type=canvas&viewport=275%2C179%2C0.06&t=uFzhnjl240XGxJ4u-1&scaling=contain&content-scaling=fixed&starting-point-node-id=2346%3A28127) and [wrist devices](https://www.figma.com/proto/X5FIVdsP2S1bFrMx241lQ5/DECO3500-Progress-UI---Final-ver?page-id=2001%3A33042&node-id=2001-33126&node-type=canvas&viewport=350%2C179%2C0.1&t=2iDlnNfuYctNtXDj-1&scaling=scale-down&content-scaling=fixed&starting-point-node-id=2001%3A33126)(present using mobile phones). Ideally, these flows are automatic along with time and detections in our design. However, for flexible process control during the exhibition, currently, most interactions between screens are clicking. A demonstrator will operate these clicks for users to help them experience the “automatic” flow.

The rewards (decoration & collaboration network map) are also mimicked with Figma, allowing viewing projection effects with a smartphone in the handmade projector. 


Please refer to [HTML for Voice input](https://lightskyblue.github.io/ShallWeCook/voice.html) to try the voice input function

The voice input system allows users to discuss milestones verbally. By visiting the provided link and clicking the "Start" button, users can enable the microphone and begin speaking. After speaking, users click "Stop" to display the transcribed discussion. Input each milestone separately to ensure more accurate recognition. The system uses HTML and CSS for layout, with JavaScript handling the Chrome Web Speech API for voice input.


Please refer to [HTML for Progress bar](https://lightskyblue.github.io/ShallWeCook/progress_bar.html) to check the progress bar function

The progress bar system visually represents how milestones show on projection. After completing the pre-setup, characters will move toward the next milestone with time passing, indicating user progress. When reaching a milestone, a pop-up prompt requires user confirmation to continue. This process repeats until all milestones are completed. The progress bar is built using HTML and CSS, while JavaScript manages the animation and milestone transitions.


# Arduino - Main function 
We use two Arduino boards as the main controllers, each equipped with an ultrasonic sensor, vibration motor, MPU6050 accelerometer, and sound sensor, functioning as wearable devices attached to users' wrists. The system has several key functions:
Haptic Notification for Problem-Solving: Users touch each other’s wrist devices to trigger haptic notifications, reminding them to select a learning method when encountering a problem. The ultrasonic sensors detect the distance between users' wrists, activating the vibration motor if the detected distance is less than 5 cm.

"You Try It" Role Swapping: After a teacher's demonstration, learners can practise by swapping roles. Users move their hands while swapping locations. This motion is detected using both the ultrasonic sensor and the MPU6050, which reads distance, accelerometer, and gyroscope data to monitor movement. The system recognizes a role swap when the accelerometer data (ax) changes from below 10,000 to above 12,000 and back to below 10,000, while the ultrasonic sensor detects a distance change from over 120 cm to less than 40 cm and back to over 120 cm. This functionality is controlled by the demonstrator only when pressing the "A" key, and the vibration motor provides haptic feedback when these three conditions are met. The demonstrator could stop the vibration by pressing the "K" key.

Silence Detection for Pop-up Chat Topics: The sound sensor continuously monitors sound levels. If the sound value remains below 20 for more than 2 minutes, the vibration motor triggers to prompt users that it is time to engage in conversation.

### NFC for object recognition ###
NFC technology is used to detect interactions between the user's wrist device and kitchen tools or condiments. Due to the high cost of the equipment (NFC detection module for Arduino is too expensive), we used a smartphone to simulate the wrist device’s display. When the wrist device approaches a designated utensil, the smartphone screen automatically switches to the confirmation interface for that utensil. Moreover, when the user is seasoning the dish, the wrist device will display corresponding prompts based on the pre-set food preferences, reminding the user of key seasoning considerations. 

![NFC Shortcut](https://github.com/DECO3500Project/DECO3500_Project/blob/main/image/3-Tradeshow/Shortcuts.jpg)
![NFC tools](https://github.com/DECO3500Project/DECO3500_Project/blob/main/image/3-Tradeshow/NFC%20tools.jpg)

# Contact Us
Contact Us
If you have any questions or suggestions, you can reach us by email at lony98.a@gmail.com
