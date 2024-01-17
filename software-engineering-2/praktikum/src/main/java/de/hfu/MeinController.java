package de.hfu;

import java.security.Principal;
import java.util.Date;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.servlet.ModelAndView;

import de.hfu.messages.domain.model.Message;
import de.hfu.messages.domain.model.User;
import de.hfu.messages.domain.service.MessageService;
import de.hfu.messages.domain.service.SecurityService;

@Controller
public class MeinController {

    private MessageService messageService;
    private SecurityService securityService;

    @RequestMapping(value = "/")
    public String home() {
        return "index.html";
    }

    @RequestMapping("/ajax/messages.json")
    @ResponseBody
    public List<Message> messages(@RequestParam(required = false) Long lastClientMessage) {
        if (lastClientMessage == null) {
            lastClientMessage = 0L;
        }
        return messageService.findLatestMessages(new Date(lastClientMessage));
    }

    @RequestMapping(value = "/messages.html")
    public ModelAndView allMessages() {
        ModelAndView mav = new ModelAndView();
        List<Message> messages = messageService.findAllMessages();

        mav.addObject("messages", messages);
        mav.addObject("lastClientMessage", (messages.size() == 0) ? 0 : messages.get(0).getDate().getTime());
        mav.setViewName("nachrichtenListe");

        return mav;
    }

    @RequestMapping(value = "/users.html")
    public ModelAndView allUsers() {
        ModelAndView mav = new ModelAndView();
        mav.addObject("users", messageService.findAllUsers());
        mav.setViewName("users");
        return mav;
    }

    @RequestMapping(value = "/login.html")
    public String login() {
        return "login";
    }

    @RequestMapping(value = "/register.html")
    public ModelAndView registerInput() {
        ModelAndView mav = new ModelAndView();
        mav.setViewName("registration");
        return mav;
    }

    @RequestMapping(value = "/save.html")
    public ModelAndView registerSave(String username, String password, String fullname, String email) {
        ModelAndView mav = new ModelAndView();

        System.out.println("registering user " + username);

        User registerUser = new User(username, securityService.encodePassword(password), fullname, email);

        try {
            messageService.createUser(registerUser);
            mav.setViewName("registrationSuccess");
        } catch (Exception exception) {
            mav.addObject("fehler", exception.getMessage());
            mav.setViewName("registration");
            System.out.println("cannot create user " + username + ": " + exception.getMessage());
        }

        return mav;
    }

    @RequestMapping(value = "/messageForm.html")
    public String messageForm() {
        return "messageForm";
    }

    @RequestMapping(value = "/createMessage.html")
    public ModelAndView createMessage(@RequestParam("messageText") String text, Principal principal) {
        System.out.println("user: " + principal.getName() + ", message: " + text);

        User user = messageService.findUserByUsername(principal.getName());
        Message message = new Message(text, new Date(), user);

        messageService.saveMessage(message);

        return allMessages();
    }

    @Autowired
    public void setMessageService(MessageService messageService) {
        this.messageService = messageService;
    }

    @Autowired
    public void setSecurityService(SecurityService securityService) {
        this.securityService = securityService;
    }

}
