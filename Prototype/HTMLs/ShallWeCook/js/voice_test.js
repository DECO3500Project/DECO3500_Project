document.addEventListener('DOMContentLoaded', () => {
    const startBtn = document.getElementById('start-btn');
    const stopBtn = document.getElementById('stop-btn');
    const resultDiv = document.getElementById('result');

    const recognition = new webkitSpeechRecognition();
    recognition.lang = 'en';  // Set the language to English
    recognition.continuous = true;  // Keep the recognition running continuously
    recognition.interimResults = true;  // Capture partial results

    let totalTranscript = '';  // Store the complete transcript of all sessions
    let currentTranscript = ''; // Store the transcript of the current session
    let hasInput = false;  // Flag to indicate whether there is any input

    startBtn.addEventListener('click', () => {
        recognition.start();  // Start speech recognition
        resultDiv.textContent = "Listening...";  // Display message indicating it's listening
        currentTranscript = '';  // Clear current transcript when a new session starts
        hasInput = false;  // Reset the input flag
    });

    recognition.onresult = (event) => {
        const last = event.results[event.results.length - 1];  // Only process the last result
        if (last.isFinal) {
            currentTranscript += last[0].transcript;  // Append the new result to the current session's transcript
            resultDiv.innerHTML = `Voice results: ${totalTranscript}<br>${currentTranscript}`;  // Display the accumulated results
            hasInput = true;  // Set input flag to true, indicating speech has been recognized
        }
    };

    recognition.onerror = (event) => {
        resultDiv.textContent = 'Error: ' + event.error;  // Display error message in case of recognition failure
    };

    stopBtn.addEventListener('click', () => {
        recognition.stop();  // Stop speech recognition
        if (hasInput) {
            totalTranscript += currentTranscript + '<br>';  // Add the current session's transcript to the total transcript and insert a line break
            resultDiv.innerHTML = `Final results: <br>${totalTranscript}`;  // Display the final transcript with line breaks
        } else {
            resultDiv.textContent = "No input detected. Please click 'Start' and try again.";  // Inform the user if no input was detected
        }
    });
});
