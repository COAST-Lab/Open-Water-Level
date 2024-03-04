# Particle Cloud—->Google Sheets Integration
1. Get an access token https://docs.particle.io/reference/cloud-apis/access-tokens/
2. Create a new google sheet
3. In google sheets, navigate to Extenstions-->Apps Script
4. Copy and paste the particle_integration.js file into the Apps Script
5. Replace `{YOUR_PARTICLE_TOKEN_HERE}` with your token from #1
6. Save/rename apps script
7. Deploy-->New Deployment (if first time deploying)
8. Select type-->Web App
9. Execute as-->Me
10. Who has access-->Anyone
11. Deploy-->Authorize access-->click through and allow
12. Under Web app and URL, there should be a URL beginning https://script...; click Copy
13. In console.particle.io, navigate to your product (or device) and create a new integration
14. Create Webhook and select edit-->Custom template
15. Copy and paste text from particle_integration.json and replace `{GOOGLE_SHEETS_SCRIPT_URL}` with the URL that you get after deploying the apps script (Step 12). Save.
16. Run your Particle firmware that is supposed to publish to the cloud and check if it ran at all (e.g., any LED or Log indicators), then check the device in console.particle.io to see if it published, check the integration to see if it triggered, and check your google sheet to see if the data have shown up.

## Credit
This routine borrows from and slightly updates [https://docs.particle.io/integrations/community-integrations/publish-to-google-sheets/](https://docs.particle.io/integrations/community-integrations/publish-to-google-sheets/). Hints on what needed to be updated came largely from [https://community.particle.io/t/pushing-data-to-google-sheets-new-thread/60138](https://community.particle.io/t/pushing-data-to-google-sheets-new-thread/60138).