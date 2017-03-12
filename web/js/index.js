// IIFE - Immediately Invoked Function Expression
(function($, particle, window, document) {
  // The $ is now locally scoped
  $(function() {
    particle = new Particle();

    // Enter your credentials
    let config = {
      username: '###@###.##',
      password: '####',
      deviceName: '####',
      // don't edit below
      accessToken: '?',
      deviceId: '?'
    }

    // disable all interaction until your logged in and connected with the device
    $('#command').hide();
    let loggedIn = false;


    // let's login
    particleLogin(config.username, config.password);


    /*
     * Buttons for specific commands to be sent to the cloud
     */
    $('#command button').each(function() {
      $(this)
        .on('click', function(e) {
          if (loggedIn !== false) {
            e.preventDefault();

            let command = $(this).attr('value');

            console.log('Sent command:', command);
            particleCallFunction(command);

            $(this)
              .css({ 'opacity': .5 })
              .animate({ 'opacity': 1 });
          }
        })
    });


    /*
     * Send command to the cloud
     */
    function particleCallFunction(arg) {
      // send a command to the function command() in the photon
      particle
        .callFunction({
          deviceId: config.deviceId,
          name: 'command',
          argument: arg,
          auth: config.accessToken
        })
        .then(
          function(data) {
            console.log('Function called succesfully:', data.body.return_value);
          },
          function(err) {
            console.log('An error occurred:', err);
          });
    }


    /*
     * Login to the cloud function
     */
    function particleLogin(user, pw) {
      // login to the cloud
      particle
        .login({ username: user, password: pw })
        .then(
          function(data) {
            config.accessToken = data.body.access_token
            console.log('API call completed on promise resolve: ', config.accessToken);

            particleListDevice(config.deviceName);
          },
          function(err) {
            console.log('API call completed on promise fail: ', err);
          }
        );
    }


    /*
     * Login only to the photon with a specific name
     */
    function particleListDevice(deviceName) {
      // get device info devices
      particle
        .listDevices({ auth: config.accessToken })
        .then(
          function(devices) {
            // search for the device name
            for (var i = 0; i < devices.body.length; i++) {
              console.log('Available device names: ', devices.body[i].name);

              // get id from device
              if (devices.body[i].name === deviceName) {
                config.deviceId = devices.body[i].id;
                console.log('Device found: ', devices.body[i].name, devices.body[i].id);

                // ok activate interaction
                $('#command').show();
                loggedIn = true;
                console.log('You are logged in and can use the device now :)');

              }
            }

            // particleGetVar('ps-voltage');

            // show the available commands when connection to the device has been established
          },
          function(err) {
            console.log('List devices call failed: ', err);
          }
        );
    }


    /*
     * Get callbacks
     */
    function particleGetVar(varName) {
      // get vars from photon
      particle
        .getVariable({ deviceId: config.deviceId, name: varName, auth: config.accessToken })
        .then(
          function(data) {
            console.log(data);
          },
          function(err) {
            console.log('An error occurred while getting attrs:', err);
          }
        );
    }


    /*
     * NOW YOU CAN USE THE KEYBOARD AS WELL!
     */
    $(window).on("keydown", function(event) {
      console.log(event.type, ": ", event.key);
      switch (event.key) {
        case 'w':
          clkBtn('FWRD');
          break;

        case 'd':
          clkBtn('STRT');
          break;

        case 's':
          clkBtn('BKWD');
          break;

        case 'a':
          clkBtn('STLT');
          break;

        case 'e':
          clkBtn('TRCW');
          break;

        case 'q':
          clkBtn('TRCC');
          break;

        case 'l':
          clkBtn('LED7');
          break;

        case '1':
          clkBtn('P1');
          break;

        case 'Shift':
        default:
          clkBtn('STOP');
          break;
      }
    });

    function clkBtn(value) {
      $('#command button[value=' + value + ']')
        .click();
    }

  });
}(window.jQuery, window.particle, window, document));
// The global jQuery object is passed as a parameter
