package de.hfu;

import de.hfu.messages.domain.model.Message;
import de.hfu.messages.domain.service.MessageService;
import java.util.List;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

@Component
public class MessagePrinter {
    @Autowired
    private MessageService messageService;

    public void printAllMessages() {
        List<Message> msgs = messageService.findAllMessages();

        for (Message msg : msgs) {
            System.out.println(msg.getText());
        }
    }

    public void setMessageService(MessageService messageService) {
        this.messageService = messageService;
    }
}
