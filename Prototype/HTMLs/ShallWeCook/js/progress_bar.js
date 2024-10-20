// Get inner_progress_bar, person, and all circles
const innerProgressBar = document.getElementById('inner-progress-bar');
const person = document.getElementById('person');
const circles = document.querySelectorAll('.circle');

// Animation duration (in milliseconds)
const duration = 100000; // Completion time: 10 minutes

// Start time and status
let start = null;
let isPaused = false; // Flag to indicate if the animation is paused
let currentCircleIndex = 1; // Index of the current circle reached
let previousProgress = 0; // Save progress when the animation was paused

// Get the width of the progress bar container
const progressBarContainer = document.getElementById('progress-bar-container');
const progressBarWidth = progressBarContainer.offsetWidth; 

// Set the initial width to 3.5%
innerProgressBar.style.width = '3.5%';

// Calculate the actual position of each circle
const circlePositions = Array.from(circles).map(circle => {
    const circleOffset = circle.offsetLeft - 10; // Get the offset of each circle relative to the left side of the parent container
    return circleOffset / (progressBarWidth); // Convert the position into a percentage of the relative width
});

// Function to update the animation
function animateProgressBarAndPerson(timestamp) {
    // If the animation is paused, do not continue
    if (isPaused) return;

    // Initialize the start time
    if (!start) start = timestamp;

    // Calculate elapsed time
    const elapsed = timestamp - start;

    // Calculate the current progress, ensuring it resumes from the last paused point and eventually reaches 96.5%
    const progress = Math.min(elapsed / duration, 1); 
    const adjustedProgress = previousProgress + (0.93 * progress); 

    // Update the width of inner_progress_bar
    innerProgressBar.style.width = (0.035 + adjustedProgress) * 100 + '%'; // Continue from previousProgress
    
    // Update the position of the person
    let newPosition = (0.035 + adjustedProgress) * progressBarWidth - 28; 

    
    const maxPosition = 1040; // Precise position of the endpoint

    // If newPosition exceeds the endpoint, force the person to stop at the endpoint
    if (newPosition > maxPosition) {
        newPosition = maxPosition;
    }

    // Dynamically update the position of the person
    person.style.transform = `translateX(${newPosition}px)`;

    // Check if the person has reached each circle and pause the animation
    if (currentCircleIndex < circles.length && adjustedProgress >= circlePositions[currentCircleIndex]) {
        // Change the style of the circle and inner-circle
        circles[currentCircleIndex].style.border = '0.1rem solid black';
        circles[currentCircleIndex].querySelector('.inner-circle').style.backgroundColor = '#A3D65C'; 
        circles[currentCircleIndex].querySelector('.inner-circle').style.border = '0.1rem solid black'; 

        // Pause the animation and wait for user confirmation
        isPaused = true;

        // Display confirmation dialog
        setTimeout(() => {
            const userConfirmed = confirm(`Milestone ${currentCircleIndex + 1}: Have you completed this milestone?`);

            // If the user confirms, continue the animation
            if (userConfirmed) {
                isPaused = false; 
                currentCircleIndex++;
                previousProgress = adjustedProgress; 
                start = null; 
                requestAnimationFrame(animateProgressBarAndPerson); 
            }
        }, 100);
    } else if (adjustedProgress >= 0.965) {
        // If the progress bar reaches the endpoint, stop the person's movement
        person.style.transform = `translateX(${newPosition}px)`; 
        return; 
    } else {
        // If the progress is not yet complete, continue to the next frame
        if (progress < 1) {
            requestAnimationFrame(animateProgressBarAndPerson);
        }
    }
}

// Start the animation
requestAnimationFrame(animateProgressBarAndPerson);
